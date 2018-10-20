// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDesc.h"
#include "list"

typedef std::list<ItemType> ItemList;

/**
 * ĳ���Ͱ� ����ִ� �κ��丮
 */
class SURVIVALPROJECT_API InventoryManager
{
public:
	InventoryManager();
	~InventoryManager();

    void AddItem(const ItemType uid) { _itemlist.push_back(uid); }
    void DeleteItem(const ItemType uid) { _itemlist.remove(uid); }

private:
    ItemList _itemlist;
};
