// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>


class MYPROJECT_API Turtle
{
private:
	std::string sentence;
	float length;
	float angle;

public:
	Turtle(std::string s, float l, float t);
	void render();
	void setLength(float f);
	void setAngle(float a);
	void setSentence(std::string s);
	~Turtle();
};
