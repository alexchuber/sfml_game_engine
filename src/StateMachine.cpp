#include "StateMachine.hpp"

void GatorEngine::StateMachine::AddState(StateRef newState, bool isReplacing)
{
	this->_isAdding = true;
	this->_isReplacing = isReplacing;
	this->_newState = std::move(newState);
}

void GatorEngine::StateMachine::RemoveState()
{
	this->_isRemoving = true;
}

void GatorEngine::StateMachine::ProcessStateChanges()
{
	if (this->_isRemoving && !this->_states.empty())
	{
		this->_states.pop();
		if (!this->_states.empty())
		{
			this->_states.top()->Resume();
		}
		this->_isRemoving = false;
	}

	if (this->_isAdding)
	{
		if (!this->_states.empty())
		{
			if (this->_isReplacing)
			{
				this->_states.pop();
			}
			else
			{
				this->_states.top()->Pause();
			}
		}

		this->_states.push(std::move(this->_newState));
		this->_states.top()->Init();
		this->_isAdding = false;
	}
}

GatorEngine::StateRef& GatorEngine::StateMachine::GetActiveState()
{
	
	return this->_states.top();
}



