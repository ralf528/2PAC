// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "string"

typedef int ItemType;

/**
 * 월드에 스폰되고 캐릭터가 획득할 수 있는 아이템
 */
class SURVIVALPROJECT_API ItemDesc
{
public:
	ItemDesc();
	~ItemDesc();

    const ItemType GetItemId() { return _uid; }
    const char* GetIconPath() { return _iconPath.c_str(); }
    const char* GetModelPath() { return _modelPath.c_str(); }
    const char* GetDescription() { return _desc.c_str(); }

private:
    const ItemType _uid;
    const std::string _iconPath;
    const std::string _modelPath;
    const std::string _desc;
};
