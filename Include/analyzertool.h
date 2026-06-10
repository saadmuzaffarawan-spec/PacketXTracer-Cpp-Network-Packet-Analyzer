#pragma once
#include <string>

class AnalyzerTool{
public:
    virtual std::string displayName(){
        return "Analyzer Tool";
    }
};