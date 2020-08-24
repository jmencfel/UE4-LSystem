// Fill out your copyright notice in the Description page of Project Settings.

#include "Turtle.h"

Turtle::Turtle(std::string s, float l, float t)
{
	sentence = s;
	length = l;
	angle = t;
}
void Turtle::render()
{
	for (int i = 0; i < sentence.length(); i++)
	{
		char c = sentence.at(i);
		if (c == 'F')
		{
			//draw line
			
		}
		else if (c == '+')
		{
			
		}
	}
}

void Turtle::setAngle(float a) { angle = a; }
void Turtle::setLength(float a) { length = a; }
void Turtle::setSentence(std::string a) { sentence = a; }

Turtle::~Turtle()
{
}
