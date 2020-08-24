// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <iostream>
#include <string>
#include "CoreMinimal.h"

using namespace std;
/**
 * 
 */
class MYPROJECT_API Rule
{
private:
	char a;
	string b;
public:
	Rule();
	Rule(char a_, string b_);
	~Rule();
	int getLength();
	char getA() {return a;}
	string getB() {return b;}
	
};
