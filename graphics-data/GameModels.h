
#pragma once
#include "VertexFormat.h"
#include <vector>
#include <map>

using namespace std;

namespace Models
{

	struct Model
	{
		unsigned int vao;
		vector <unsigned int> vbos;
		Model(){}
	};
	class GameModels
	{
	public:
		GameModels();
		~GameModels();
		void CreateTriangleModel(const string &gameModelName);
		void DeleteModel(const string& gameModelName);
		unsigned int GetModel(const string &gameModelName);
	private: 
		map<string, Model> GameModelList;
};

}
