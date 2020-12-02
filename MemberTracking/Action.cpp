#include "Action.h"


void ActionAdd::executeUndo()
{
	repository->deleteMember(addedMember.getName());
}

void ActionAdd::executeRedo()
{
	repository->addMember(addedMember);
}


void ActionUpdate::executeUndo()
{
	repository->updateMember(updatedMember);
}

void ActionUpdate::executeRedo()
{
	repository->updateMember(afterUpdate);
}


void ActionDelete::executeUndo()
{
	repository->addMember(deletedMember);
}

void ActionDelete::executeRedo()
{
	repository->deleteMember(deletedMember.getName());
}
