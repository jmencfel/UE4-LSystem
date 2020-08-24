// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include <vector>

#include "Rule.h"

class MYPROJECT_API LSystem
{
private:
	string sentence;     // The sentence (a String)
	Rule ruleset[6];      // The ruleset (an array of Rule objects)
	int generation;      // Keeping track of the generation #
	std::vector<Rule> rules;
public:
	LSystem();
	void setType(string tag);
	LSystem(string axiom, Rule ruleset[2]);
	void generate();
	string rulePicker(char x);
	string getSentence() {return sentence;}
	int getGeneration() {return generation;}
	~LSystem();
};
