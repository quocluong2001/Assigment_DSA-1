#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

ringsignList* createRingsignNode(int nRingsign)
{
	ringsignList* node = new ringsignList;
	node->nRingsign = nRingsign;
	node->pNext = NULL;
	return node;
}

//return size of ringsignList
int countRignsign(ringsignList* pList)
{
	if (pList == NULL)
		return 0;
	ringsignList* current = pList;
	int count = 0;
	while (current != NULL)
	{
		++count;
		current = current->pNext;
	}
	return count;
}

//add tail
void addRingsign_tail(ringsignList*& pList, int nRingsign)
{
	ringsignList* node = createRingsignNode(nRingsign);
	if (countRignsign(pList) == 0)
		pList = node;
	else
	{
		ringsignList* current = pList;
		while (current->pNext != NULL)
			current = current->pNext;
		current->pNext = node;
	}
}

void addRingsign_head(ringsignList*& pList, int nRingsign)
{
	ringsignList* node = createRingsignNode(nRingsign);
	if (countRignsign(pList) == 0)
		pList = node;
	else
	{
		node->pNext = pList;
		pList = node;
	}
}

void addRingsign_index(ringsignList*& pList, int nRingsign, int index)
{
	int size = countRignsign(pList);
	if (index >= size && index <= size)
	{
		if (index == 0) addRingsign_head(pList, nRingsign);
		else if (index == size) addRingsign_tail(pList, nRingsign);
		else
		{
			int currIndex = 0;
			ringsignList* node = createRingsignNode(nRingsign);
			ringsignList* current = pList;
			while (currIndex != index - 1)
			{
				current = current->pNext;
				++currIndex;
			}
			node->pNext = current->pNext;
			current->pNext = node;
		}
	}
}

void removeAt(ringsignList*& pList, int index)
{
	int size = countRignsign(pList);
	ringsignList* current = pList;
	if (index >= 0 && index < size)
	{
		if (index == 0)
		{
			pList = pList->pNext;
			current->pNext = NULL;
			delete current;
			return;
		}
		int currIndex = 0;
		while (currIndex != index - 1)
		{
			current = current->pNext;
			++currIndex;
		}
		ringsignList* tmp = current->pNext;
		current->pNext = current->pNext->pNext;
		tmp->pNext = NULL;
		delete tmp;
	}
}

void clear(ringsignList*& pList)
{
	int size = countRignsign(pList);
	for (int i = 0; i < size; ++i) removeAt(pList, 0);
}

ringsignList* reverse(ringsignList*& pList)
{
	int size = countRignsign(pList);
	int* arr = new int[size];
	int i = 0;
	ringsignList* current = pList;

	while (current != NULL)
	{
		arr[i] = current->nRingsign;
		++i;
		current = current->pNext;
	}

	clear(pList);

	for (int i = size - 1; i >= 0; --i) addRingsign_tail(pList, arr[i]);
	delete[] arr;
	return pList;
}

string getCharacter(int maxHP)
{
	if (maxHP == 777) return "Isildur";
	else if (maxHP == 888) return "Legolas";
	else if (maxHP == 999) return "Gandalf";
	else return "";
}

bool IsDead(knight theKnight, ringsignList*& pList)
{
	if (theKnight.HP <= 0)
	{
		clear(pList);
		return true;
	}
	return false;
}

bool Uruk_hai(int eventCode)
{
	if (eventCode >= 10 && eventCode <= 19) return true;
	return false;
}

bool Ringwraiths(int eventCode)
{
	if (eventCode >= 20 && eventCode <= 29) return true;
	return false;
}

bool Strider(int eventCode)
{
	if (eventCode >= 30 && eventCode <= 39) return true;
	return false;
}

bool Gollum(int eventCode)
{
	if (eventCode >= 40 && eventCode <= 49) return true;
	return false;
}

bool Lurtz(int eventCode)
{
	if (eventCode >= 50 && eventCode <= 59) return true;
	return false;
}

bool Gimli(int eventCode)
{
	if (eventCode >= 60 && eventCode <= 69) return true;
	return false;
}

bool Saruman(int eventCode)
{
	if (eventCode >= 90 && eventCode <= 99) return true;
	return false;
}

int getlevelO(int eventIndex)
{
	int b = eventIndex % 10;
	int level = eventIndex > 6 ? (b > 5 ? b : 5) : b;
	return level;
}

double getBasedamage(int eventCode)
{
	if (Uruk_hai(eventCode)) return 1;
	else if (Ringwraiths(eventCode)) return 1.8;
	else if (Strider(eventCode)) return 4.5;
	else if (Gollum(eventCode)) return 8.2;
	else if (Lurtz(eventCode)) return 7.5;
	else if (Gimli(eventCode)) return 9;
	else if (Saruman(eventCode)) return 0.1;
	return 0;
}

void loseGollum(ringsignList*& pList, int eventCode)
{
	int GollumRingsign = eventCode % 10;
	int countDuplicate = 0;
	ringsignList* current = pList;
	int currIndex = 0;
	while (current != NULL)
	{
		if (current->nRingsign == GollumRingsign)
			++countDuplicate;
		current = current->pNext;
	}

	if (countDuplicate == 0) return;

	current = pList;
	while (current != NULL)
	{
		if (current->nRingsign == GollumRingsign)
		{
			--countDuplicate;
			if (countDuplicate == 0) break;
		}
		current = current->pNext;
		++currIndex;
	}
	removeAt(pList, currIndex);
}

void loseLurtz(ringsignList*& pList)
{
	int size = countRignsign(pList);
	if (size <= 3) clear(pList);
	else
	{
		for (int i = 0; i < 3; ++i) removeAt(pList, 0);
	}
}

void loseSaruman(ringsignList*& pList, int eventCode)
{
	int SarumanRingsign = eventCode % 10;

	while (pList->nRingsign == SarumanRingsign)
	{
		removeAt(pList, 0);
		if (pList == NULL) return;
	}

	ringsignList* current = pList;
	int currIndex = 0;

	while (current != NULL)
	{
		if (current->pNext != NULL)
		{
			if (current->pNext->nRingsign == SarumanRingsign)
			{
				int tmp = currIndex + 1;
				removeAt(pList, tmp);
			}
		}
		current = current->pNext;
		++currIndex;
	}
}

void fightEnemy(knight& theKnight, ringsignList*& pList, int eventCode, int eventIndex, int maxHP)
{

	int levelO = getlevelO(eventIndex);

	if (theKnight.level == levelO ||
		(getCharacter(maxHP) == "Legolas" && (Strider(eventCode) || Gimli(eventCode))) ||
		(getCharacter(maxHP) == "Gandalf" && (Uruk_hai(eventCode) || Ringwraiths(eventCode) || Gimli(eventCode))))
		return;

	else if (theKnight.level > levelO)
	{
		if (!Saruman(eventCode))
			addRingsign_tail(pList, eventCode % 10);
		if (Saruman(eventCode)) pList = reverse(pList);
	}

	else
	{
		double baseDamage = getBasedamage(eventCode);
		double Damage = baseDamage * (double)levelO * 10;
		theKnight.HP -= (int)Damage;
		if (Gollum(eventCode) && getCharacter(maxHP) != "Isildur") loseGollum(pList, eventCode);
		else if (Lurtz(eventCode) && getCharacter(maxHP) != "Isildur") loseLurtz(pList);
		else if (Saruman(eventCode) && getCharacter(maxHP) != "Isildur") loseSaruman(pList, eventCode);
	}
}

bool checkSpecialArwen(ringsignList* pList)
{
	ringsignList* current = pList;
	while (current != NULL)
	{
		if (current->nRingsign != 9)
			return 0;
		current = current->pNext;
	}
	return 1;
}

ringsignList* meetArwen(int eventCode, ringsignList*& pList)
{
	if (countRignsign(pList) == 0) return pList;

	while (pList->nRingsign == 0)
	{
		removeAt(pList, 0);
		if (pList == NULL) break;
	}

	if (countRignsign(pList) == 0) addRingsign_head(pList, 1);
	else if (checkSpecialArwen(pList))
	{
		ringsignList* current = pList;
		while (current != NULL)
		{
			current->nRingsign = 0;
			current = current->pNext;
		}
		addRingsign_head(pList, 1);
	}
	else
	{
		int size = countRignsign(pList);
		int* arr = new int[size];
		ringsignList* current = pList;
		for (int i = 0; i < size; ++i)
		{
			arr[i] = current->nRingsign;
			current = current->pNext;
		}
		clear(pList);
		for (int i = size - 1; i >= 0; --i)
		{
			if (arr[i] == 9) arr[i] = 0;
			else
			{
				++arr[i];
				break;
			}
		}
		for (int i = 0; i < size; ++i) addRingsign_tail(pList, arr[i]);
	}
	return pList;
}

void meetGaladriel(ringsignList*& pList, knight& theKnight, int maxHP)
{
	if (theKnight.HP < maxHP)
	{
		theKnight.HP = maxHP;
		if (getCharacter(maxHP) != "Isildur" && getCharacter(maxHP) != "Legolas")
		{
			int size = countRignsign(pList);
			removeAt(pList, size - 1);
		}
	}
}

ringsignList* combat(knight& theKnight, eventList* pEvent)
{
	ringsignList* pList = NULL;
	//fighting for honor and love here
	addRingsign_head(pList, theKnight.nInitRingsign);
	int eventIndex = 1;
	int maxHP = theKnight.HP;

	while (pEvent != NULL)
	{
		if (pEvent->nEventCode == 0 || IsDead(theKnight, pList))
			break;
		else if ((pEvent->nEventCode >= 10 && pEvent->nEventCode <= 69) || 
				 (pEvent->nEventCode >= 90 && pEvent->nEventCode <= 99))
			fightEnemy(theKnight, pList, pEvent->nEventCode, eventIndex, maxHP);
		else if (pEvent->nEventCode == 7)
			pList = meetArwen(pEvent->nEventCode, pList);
		else if (pEvent->nEventCode == 8)
			meetGaladriel(pList, theKnight, maxHP);

		if (IsDead(theKnight, pList) || countRignsign(pList) == 0)
			break;

		//if (pEvent != NULL)
		//	cout << "After Event: " << pEvent->nEventCode << "\t" << "LV: " << getlevelO(eventIndex) << "\t" << "HP: " << theKnight.HP << "\t"; //FIXME:


		++eventIndex;
		pEvent = pEvent->pNext;

		
		//// FIXME:
		//ringsignList* copyEnd = pList;
		//while (copyEnd != NULL)
		//{
		//	cout << copyEnd->nRingsign;
		//	copyEnd = copyEnd->pNext;
		//}
		//cout << endl;
	}
	return pList;
}

int checkPalindrome(ringsignList* pRingsign)
{
	int size = countRignsign(pRingsign);
	if (size == 0) return 0;
	int* arr = new int[size];
	ringsignList* current = pRingsign;
	int i = 0;
	while (current != NULL)
	{
		arr[i] = current->nRingsign;
		++i;
		current = current->pNext;
	}
	for (int i = 0; i < size / 2; ++i)
	{
		if (arr[i] != arr[size - i - 1])
		{
			delete[] arr;
			return 0;
		}
	}
	return 1;
}
