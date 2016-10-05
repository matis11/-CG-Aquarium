#include "fish.h"

namespace Models {

	void Model::drawSolid() {
		glEnableClientState(GL_VERTEX_ARRAY);
		////glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		/*cout << "Draw Solid" << endl;
		for (int i = 0; i<10; i++) {
		cout << i << ":  " << vertexNormals[i] << endl;
		}
		cout << "VertexCount" <<  vertexCount << endl;*/

		glVertexPointer(4, GL_FLOAT, 0, this->vertices);
		////glColorPointer(4,GL_FLOAT,0,colors);
		glNormalPointer(GL_FLOAT, sizeof(float) * 4, this->vertexNormals);
		glTexCoordPointer(2, GL_FLOAT, 0, this->texCoords);

		glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

		glDisableClientState(GL_VERTEX_ARRAY);
		////glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void Model::drawWire() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		drawSolid();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Model::loadOBJ(char filename[]) {
		cout << "LOADING OBJECT: " << filename << endl;
		this->vertexCount = 0;
		ifstream Plik;
		Plik.open(filename);
		string dane;
		if (!Plik) cerr << "Couldn't open " << filename << " for reading\n";

		string temp;
		int v = 0;
		int vn = 0;
		int  vt = 0;
		int f = 0;

		while (!Plik.eof()) {
			Plik >> temp;
			if (temp == "v") v++;
			if (temp == "vn") vn++;
			if (temp == "vt") vt++;
			if (temp == "f") f++;
		}

		this->vertexCount = f * 3;
		v = v * 3;
		float * tempvertices = new float[v];

		vn = vn * 3;
		float * tempvertexNormals = new float[vn];

		vt = vt * 2;
		float * temptexCoords = new float[vt];

		int **TVertices = new int*[f];
		int **TNormals = new int*[f];
		int **TTexCoords = new int*[f];

		for (int i = 0; i < f; i++) {
			TVertices[i] = new int[3];
			TNormals[i] = new int[3];
			TTexCoords[i] = new int[3];
		}

		Plik.clear();
		Plik.seekg(0, ios::beg);
		int iN = 0;
		int iVN = 0;
		int iVT = 0;
		int iF = 0;

		while (!Plik.eof()) {
			Plik >> temp;
			/******** writinig into vertices table *****/
			if (temp == "v") {
				for (int j = 0; j < 3; j++) {
					Plik >> temp;
					tempvertices[iN] = atof(temp.c_str());
					//	cout << "iN: "<<  iN << endl;
					iN++;
				}
				continue;
			}
			else if (temp == "vn") {
				/*** writinig into vertexNormals table ***/
				for (int j = 0; j<3; j++) {
					Plik >> temp;
					tempvertexNormals[iVN] = atof(temp.c_str());
					//cout << "iVN: " << iVN << endl;
					iVN++;
				}
				continue;
			}
			else if (temp == "vt") {
				/*** writinig into texCoords table ***/
				for (int j = 0; j < 2; j++) {
					Plik >> temp;
					//cout << "iVT: " << iVT << endl;
					temptexCoords[iVT] = atof(temp.c_str());
					iVT++;
				}
				continue;
			}
			else if (temp == "f") {
				/*** writinig into texCoords table ***/
				for (int j = 0; j < 3; j++) {
					Plik >> temp;
					sscanf_s(temp.c_str(), "%d/%d/%d", &TVertices[iF][j], &TTexCoords[iF][j], &TNormals[iF][j]);
				}
				iF++;
				continue;
			}
			else {
				getline(Plik, temp);
			}
			/******************************************/
		}

		cout << "V: " << v << endl;
		cout << "VN: " << vn << endl;
		cout << "VT: " << vt << endl;
		cout << "F: " << f << endl;
		Plik.close();

		this->vertices = new float[f * 12];
		this->vertexNormals = new float[f * 12];
		this->texCoords = new float[f * 8];

		int tempp = 0;
		int tempp2 = 0;
		for (int j = 0; j < f; j++)
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					vertices[tempp] = tempvertices[(TVertices[j][i] - 1) * 3 + k];
					vertexNormals[tempp] = tempvertexNormals[(TNormals[j][i] - 1) * 3 + k];
					tempp++;
				}
				for (int k = 0; k < 2; k++) {
					texCoords[tempp2] = temptexCoords[(TTexCoords[j][i] - 1) * 2 + k];
					tempp2++;
				}
				vertices[tempp] = 1.0f;
				vertexNormals[tempp] = 0.0f;
				tempp++;
			}

		for (int i = 0; i < f; i++) {
			delete[] TTexCoords[i];
			delete[] TNormals[i];
			delete[] TVertices[i];
		}

		delete[] TTexCoords;
		delete[] temptexCoords;
		delete[] tempvertexNormals;
		delete[] tempvertices;

	}

}

namespace Models {
	Fish fish;

	Fish::Fish() {
		if (vertexCount == 0) loadOBJ("okon.obj");
	}

	Fish::~Fish() {
	 }
	
}