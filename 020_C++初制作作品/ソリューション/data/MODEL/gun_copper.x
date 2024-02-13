xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 68;
 0.00000;47.10480;0.00000;,
 11.61040;47.10480;0.00000;,
 11.61040;-47.21320;-0.00000;,
 0.00000;-47.21320;-0.00000;,
 11.61040;47.10480;0.00000;,
 11.61040;47.10480;23.22360;,
 11.61040;-47.21320;23.22360;,
 11.61040;-47.21320;-0.00000;,
 11.61040;47.10480;23.22360;,
 0.00000;47.10480;23.22360;,
 0.00000;-47.21320;23.22360;,
 11.61040;-47.21320;23.22360;,
 0.00000;47.10480;23.22360;,
 0.00000;47.10480;0.00000;,
 0.00000;-47.21320;-0.00000;,
 0.00000;-47.21320;23.22360;,
 11.61040;47.10480;0.00000;,
 0.00000;47.10480;0.00000;,
 0.00000;-47.21320;-0.00000;,
 11.61040;-47.21320;-0.00000;,
 -7.74820;56.63660;-113.01730;,
 19.35860;56.63660;-113.01730;,
 19.35860;37.61300;-113.01730;,
 -7.74820;37.61300;-113.01730;,
 19.35860;56.63660;-113.01730;,
 19.35860;56.63660;62.04240;,
 19.35860;37.61300;62.04240;,
 19.35860;37.61300;-113.01730;,
 19.35860;56.63660;62.04240;,
 -7.74820;56.63660;62.04240;,
 -7.74820;37.61300;62.04240;,
 19.35860;37.61300;62.04240;,
 -7.74820;56.63660;62.04240;,
 -7.74820;56.63660;-113.01730;,
 -7.74820;37.61300;-113.01730;,
 -7.74820;37.61300;62.04240;,
 19.35860;56.63660;-113.01730;,
 -7.74820;56.63660;-113.01730;,
 -7.74820;37.61300;-113.01730;,
 19.35860;37.61300;-113.01730;,
 7.05350;39.33660;-16.87480;,
 4.55690;39.33660;-16.87480;,
 -2.28810;39.33660;-11.36880;,
 13.89850;39.33660;-11.36880;,
 14.54180;14.67980;-17.69220;,
 4.67710;14.67980;-18.05560;,
 5.20030;14.67980;-23.19820;,
 15.06500;14.67980;-22.83480;,
 -2.28810;28.36520;-11.36880;,
 4.67710;14.67980;-18.05560;,
 14.54180;14.67980;-17.69220;,
 13.89850;28.36520;-11.36880;,
 13.89850;39.33660;-11.36880;,
 -2.28810;39.33660;-11.36880;,
 4.55690;29.48100;-16.87480;,
 4.67710;14.67980;-18.05560;,
 -2.28810;28.36520;-11.36880;,
 -2.28810;39.33660;-11.36880;,
 7.05350;29.48100;-16.87480;,
 15.06500;14.67980;-22.83480;,
 5.20030;14.67980;-23.19820;,
 4.55690;29.48100;-16.87480;,
 4.55690;39.33660;-16.87480;,
 7.05350;39.33660;-16.87480;,
 13.89850;28.36520;-11.36880;,
 14.54180;14.67980;-17.69220;,
 7.05350;29.48100;-16.87480;,
 13.89850;39.33660;-11.36880;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;48,51,52,53;,
 4;54,46,55,56;,
 4;54,56,57,41;,
 4;58,59,60,61;,
 4;58,61,62,63;,
 4;64,65,47,66;,
 4;64,66,40,67;;
 
 MeshMaterialList {
  2;
  22;
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.655686;0.410980;0.087843;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.008562;-0.220342;0.975385;,
  -0.422050;0.119423;-0.898672;,
  0.229697;0.139523;-0.963209;,
  -0.016703;-0.429837;0.902752;,
  0.000000;0.000000;1.000000;,
  -0.880287;0.030622;-0.473453;,
  -0.768938;0.015624;-0.639132;,
  -0.626775;0.000000;-0.779200;,
  -0.332265;0.000000;-0.943186;,
  0.016959;0.391018;-0.920227;,
  0.332265;0.000000;-0.943186;,
  0.772784;0.232906;-0.590390;,
  0.832848;0.439910;-0.335921;,
  0.626775;0.000000;-0.779200;;
  22;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,17,17,14;,
  4;14,14,18,18;,
  4;15,19,19,20;,
  4;15,20,21,22;,
  4;16,23,23,15;,
  4;16,15,22,24;,
  4;25,26,26,26;,
  4;25,16,24,27;;
 }
 MeshTextureCoords {
  68;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.546580;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.563090;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.544830;,
  0.000000;1.000000;,
  0.000000;0.546580;,
  0.000000;0.000000;,
  1.000000;0.561340;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.544830;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.563090;,
  1.000000;1.000000;,
  0.000000;0.561340;,
  1.000000;0.000000;;
 }
}
