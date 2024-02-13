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
 98;
 -190.57260;322.16620;-428.55350;,
 0.00000;374.98080;-428.55350;,
 0.00000;115.29520;-428.55350;,
 -185.68260;115.29520;-428.55350;,
 190.57260;322.16620;-428.55350;,
 185.68260;115.29520;-428.55350;,
 0.00000;5.14240;-428.55350;,
 -185.68260;5.14240;-428.55350;,
 185.68260;5.14240;-428.55350;,
 190.57260;322.16620;-428.55350;,
 190.57260;322.16620;-22.31680;,
 185.68260;115.29520;-22.31680;,
 185.68260;115.29520;-428.55350;,
 190.57260;322.16620;456.40860;,
 185.68260;115.29520;456.40860;,
 185.68260;5.14240;-22.31680;,
 185.68260;5.14240;-428.55350;,
 185.68260;5.14240;456.40860;,
 190.57260;322.16620;456.40860;,
 0.00000;374.98080;456.40860;,
 0.00000;115.29520;456.40860;,
 185.68260;115.29520;456.40860;,
 -190.57260;322.16620;456.40860;,
 -185.68260;115.29520;456.40860;,
 0.00000;5.14240;456.40860;,
 185.68260;5.14240;456.40860;,
 -185.68260;5.14240;456.40860;,
 -190.57260;322.16620;456.40860;,
 -190.57260;322.16620;-22.31680;,
 -185.68260;115.29520;-22.31680;,
 -185.68260;115.29520;456.40860;,
 -190.57260;322.16620;-428.55350;,
 -185.68260;115.29520;-428.55350;,
 -185.68260;5.14240;-22.31680;,
 -185.68260;5.14240;456.40860;,
 -185.68260;5.14240;-428.55350;,
 0.00000;374.98080;-22.31680;,
 -190.57260;322.16620;-22.31680;,
 190.57260;322.16620;-22.31680;,
 0.00000;374.98080;-428.55350;,
 -190.57260;322.16620;-428.55350;,
 190.57260;322.16620;-428.55350;,
 -185.68260;5.14240;-22.31680;,
 0.00000;5.14240;-22.31680;,
 185.68260;5.14240;-22.31680;,
 -185.68260;5.14240;-428.55350;,
 0.00000;5.14240;-428.55350;,
 185.68260;5.14240;-428.55350;,
 -316.72290;261.99619;-423.28580;,
 -192.60620;362.20801;-423.28580;,
 -192.60620;324.87891;-423.28580;,
 -316.72290;224.66730;-423.28580;,
 0.00000;415.02240;-423.28580;,
 0.00000;377.69379;-423.28580;,
 192.60620;362.20801;-423.28580;,
 192.60620;324.87891;-423.28580;,
 316.72290;261.99619;-423.28580;,
 316.72290;224.66730;-423.28580;,
 316.72290;261.99619;-423.28580;,
 316.72290;261.99619;471.48792;,
 316.72290;224.66730;471.48792;,
 316.72290;224.66730;-423.28580;,
 316.72290;261.99619;471.48792;,
 192.60620;362.20801;471.48792;,
 192.60620;324.87891;471.48792;,
 316.72290;224.66730;471.48792;,
 0.00000;415.02240;471.48792;,
 0.00000;377.69379;471.48792;,
 -192.60620;362.20801;471.48792;,
 -192.60620;324.87891;471.48792;,
 -316.72290;261.99619;471.48792;,
 -316.72290;224.66730;471.48792;,
 -316.72290;261.99619;471.48792;,
 -316.72290;261.99619;-423.28580;,
 -316.72290;224.66730;-423.28580;,
 -316.72290;224.66730;471.48792;,
 -192.60620;362.20801;471.48792;,
 -192.60620;362.20801;-423.28580;,
 -316.72290;261.99619;-423.28580;,
 0.00000;415.02240;-423.28580;,
 192.60620;362.20801;471.48792;,
 192.60620;362.20801;-423.28580;,
 316.72290;261.99619;-423.28580;,
 -316.72290;224.66730;-423.28580;,
 -192.60620;324.87891;-423.28580;,
 -192.60620;324.87891;471.48792;,
 0.00000;377.69379;-423.28580;,
 192.60620;324.87891;-423.28580;,
 192.60620;324.87891;471.48792;,
 316.72290;224.66730;-423.28580;,
 -150.98560;184.72861;-430.61761;,
 -18.80470;184.72861;-430.61761;,
 -18.80470;6.24220;-430.61761;,
 -150.98560;6.24220;-430.61761;,
 -31.92730;184.72861;-311.55911;,
 -31.92730;6.24220;-311.55911;,
 -137.86310;184.72861;-311.55911;,
 -137.86310;6.24220;-311.55911;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;12,11,15,16;,
 4;11,14,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;21,20,24,25;,
 4;20,23,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;30,29,33,34;,
 4;29,32,35,33;,
 4;27,19,36,37;,
 4;19,13,38,36;,
 4;37,36,39,40;,
 4;36,38,41,39;,
 4;42,43,24,34;,
 4;43,44,17,24;,
 4;45,46,43,42;,
 4;46,47,44,43;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;72,73,74,75;,
 4;72,76,77,78;,
 4;76,66,79,77;,
 4;66,80,81,79;,
 4;80,59,82,81;,
 4;83,84,85,75;,
 4;84,86,67,85;,
 4;86,87,88,67;,
 4;87,89,60,88;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;94,96,97,95;,
 4;96,90,93,97;,
 4;96,94,91,90;,
 4;93,92,95,97;;
 
 MeshMaterialList {
  5;
  48;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  4,
  4,
  4,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\house_blood_000.png";
   }
  }
  Material {
   0.288800;0.288800;0.288800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\doar001.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\kawara000.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  44;
  0.000000;0.000000;-1.000000;,
  0.999721;-0.023631;-0.000000;,
  0.999930;-0.011816;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.999721;-0.023631;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.999930;-0.011816;-0.000000;,
  -0.999721;-0.023631;0.000000;,
  -0.999930;-0.011816;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.999721;-0.023631;-0.000000;,
  0.999930;-0.011816;-0.000000;,
  -0.999721;-0.023631;0.000000;,
  -0.999930;-0.011816;0.000000;,
  -0.999721;-0.023631;0.000000;,
  -0.999930;-0.011816;0.000000;,
  -0.267070;0.963677;0.000000;,
  -0.267070;0.963677;0.000000;,
  0.267070;0.963677;0.000000;,
  0.267070;0.963677;0.000000;,
  -0.267070;0.963677;0.000000;,
  0.267070;0.963677;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.902275;0.431162;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -0.902275;0.431162;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.455945;0.890008;0.000000;,
  0.000000;1.000000;0.000000;,
  0.455945;0.890008;0.000000;,
  0.628199;-0.778053;-0.000000;,
  0.455946;-0.890008;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.455946;-0.890008;0.000000;,
  -0.628199;-0.778053;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.993981;0.000000;0.109556;,
  0.000000;0.000000;1.000000;,
  -0.993981;0.000000;0.109555;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  48;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;12,1,2,13;,
  4;1,4,6,2;,
  4;13,2,3,3;,
  4;2,6,3,3;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;14,7,8,15;,
  4;7,16,17,8;,
  4;15,8,9,9;,
  4;8,17,9,9;,
  4;18,10,10,19;,
  4;10,20,21,10;,
  4;19,10,10,22;,
  4;10,21,23,10;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;11,11,11,11;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;25,25,27,27;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;28,28,29,29;,
  4;28,30,30,28;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,25,25,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;;
 }
 MeshTextureCoords {
  98;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  0.231650;-0.900410;,
  0.746680;-0.900410;,
  0.746680;-0.029960;,
  0.231650;-0.029960;,
  0.695550;-0.900410;,
  0.695550;-0.029960;,
  0.282780;-0.900410;,
  0.282780;-0.029960;;
 }
}
