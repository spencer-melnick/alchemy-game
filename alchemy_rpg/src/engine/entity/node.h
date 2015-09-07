#pragma once

#include <memory>
#include <vector>

namespace Engine
{

	template <typename T>
	class Node: public std::enable_shared_from_this<Node<T> > {
	public:
		void addChild(std::shared_ptr<T> child) {
			removeChild(std::weak_ptr<T>(child));
			children_.emplace(child);

			child->setOwner(std::weak_ptr<T>(shared_from_this()));
		}

		void removeChild(std::weak_ptr<T> child) {
			auto ptr = child.lock();

			auto i = children_.find(ptr);
			if (i != children_.end())
				if (i->owner_.get() == this) {
					i->owner_ = std::weak_ptr<T>();
					children_.erase(i);
				}
		}

		std::vector<std::weak_ptr<T> > getChildren() {
			std::vector<std::weak_ptr<T> > tmp(children_.size());
			for (auto i : children_)
				tmp.emplace(i);

			return tmp;
		}

		std::weak_ptr<T> getOwner() {
			return std::weak_ptr<T>(owner_);
		}

	protected:
		std::vector<std::shared_ptr<T> > children_;
		std::weak_ptr<T> owner_;

		void setParent(std::weak_ptr<T> owner) {
			if (!owner.expired())
				owner.lock()->remove(std::weak_ptr<T>(shared_from_this()));
			owner_(owner);
		}
	};

}
