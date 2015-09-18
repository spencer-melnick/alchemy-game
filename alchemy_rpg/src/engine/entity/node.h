#pragma once

#include <memory>
#include <vector>

namespace Engine
{

	template <typename T>
	class Node {
	public:
		void addChild(T* child) {
			removeChild(child);
			children_.emplace(child);

			child->setOwner(this);
		}

		void removeChild(T* child) {
			auto i = children_.find(T);
			if (i != children_.end())
				if (i->owner_ == this) {
					i->owner_ = nullptr;
					children_.erase(i);
				}
		}

		std::vector<T*> getChildren() {
			std::vector<T*> tmp(children_.size());
			tmp = children_;
			return tmp;
		}

		T* getOwner() {
			return owner_;
		}

	protected:
		std::vector<T*> children_;
		T* owner_;

		void setParent(T* owner) {
			if (owner != nullptr)
				owner_->remove(this);
			owner_ = owner;
		}
	};

}
