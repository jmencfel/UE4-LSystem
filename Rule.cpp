// Fill out your copyright notice in the Description page of Project Settings.

#include "Rule.h"
Rule::Rule()
{
	a = 'a';
	b = "ABA";
}
Rule::Rule(char a_, string b_)
{
	a = a_;
	b = b_;
}
int Rule::getLength()
{
	return b.size();
}
Rule::~Rule()
{
}
