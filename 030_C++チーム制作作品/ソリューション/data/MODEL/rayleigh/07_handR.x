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
 127;
 -2.35325;0.04544;-0.02163;,
 -2.20378;0.04544;0.04028;,
 -2.20378;0.10757;-0.03093;,
 -2.30290;0.10757;-0.07198;,
 -2.05431;0.04544;-0.02163;,
 -2.10467;0.10757;-0.07198;,
 -1.99240;0.04544;-0.17110;,
 -2.06361;0.10757;-0.17110;,
 -2.05431;0.04544;-0.32057;,
 -2.10467;0.10757;-0.27021;,
 -2.20378;0.04544;-0.38248;,
 -2.20378;0.10757;-0.31127;,
 -2.35325;0.04544;-0.32057;,
 -2.30290;0.10757;-0.27021;,
 -2.41516;0.04544;-0.17110;,
 -2.34395;0.10757;-0.17110;,
 -2.35325;0.04544;-0.02163;,
 -2.30290;0.10757;-0.07198;,
 -2.20378;-0.10483;-0.03093;,
 -2.30290;-0.10483;-0.07198;,
 -2.20378;-0.11837;-0.17110;,
 -2.10467;-0.10483;-0.07198;,
 -2.06361;-0.10483;-0.17110;,
 -2.10467;-0.10483;-0.27021;,
 -2.20378;-0.10483;-0.31127;,
 -2.30290;-0.10483;-0.27021;,
 -2.34395;-0.10483;-0.17110;,
 -2.30290;0.10757;-0.07198;,
 -2.20378;0.10757;-0.03093;,
 -2.20378;0.12111;-0.17110;,
 -2.10467;0.10757;-0.07198;,
 -2.06361;0.10757;-0.17110;,
 -2.10467;0.10757;-0.27021;,
 -2.20378;0.10757;-0.31127;,
 -2.30290;0.10757;-0.27021;,
 -2.34395;0.10757;-0.17110;,
 -2.35325;-0.04568;-0.02163;,
 -2.20378;-0.04568;0.04028;,
 -2.05431;-0.04568;-0.02163;,
 -1.99240;-0.04568;-0.17110;,
 -2.05431;-0.04568;-0.32057;,
 -2.20378;-0.04568;-0.38248;,
 -2.35325;-0.04568;-0.32057;,
 -2.41516;-0.04568;-0.17110;,
 -2.35325;-0.04568;-0.02163;,
 -2.30290;-0.10483;-0.07198;,
 -2.20378;-0.10483;-0.03093;,
 -2.10467;-0.10483;-0.07198;,
 -2.06361;-0.10483;-0.17110;,
 -2.10467;-0.10483;-0.27021;,
 -2.20378;-0.10483;-0.31127;,
 -2.30290;-0.10483;-0.27021;,
 -2.34395;-0.10483;-0.17110;,
 -2.30290;-0.10483;-0.07198;,
 -0.24318;0.07130;0.24559;,
 -0.00598;0.07130;0.34384;,
 -0.00598;0.16990;0.23084;,
 -0.16327;0.16990;0.16568;,
 0.23121;0.07130;0.24559;,
 0.15131;0.16990;0.16568;,
 0.32946;0.07130;0.00840;,
 0.21646;0.16990;0.00840;,
 0.23121;0.07130;-0.22880;,
 0.15131;0.16990;-0.14889;,
 -0.00598;0.07130;-0.32705;,
 -0.00598;0.16990;-0.21405;,
 -0.24318;0.07130;-0.22880;,
 -0.16327;0.16990;-0.14889;,
 -0.34143;0.07130;0.00840;,
 -0.22842;0.16990;0.00840;,
 -0.24318;0.07130;0.24559;,
 -0.16327;0.16990;0.16568;,
 -0.00598;-0.16716;0.23084;,
 -0.16327;-0.16716;0.16568;,
 -0.00598;-0.18864;0.00840;,
 0.15131;-0.16716;0.16568;,
 0.21646;-0.16716;0.00840;,
 0.15131;-0.16716;-0.14889;,
 -0.00598;-0.16716;-0.21405;,
 -0.16327;-0.16716;-0.14889;,
 -0.22842;-0.16716;0.00840;,
 -0.16327;0.16990;0.16568;,
 -0.00598;0.16990;0.23084;,
 -0.00598;0.19138;0.00840;,
 0.15131;0.16990;0.16568;,
 0.21646;0.16990;0.00840;,
 0.15131;0.16990;-0.14889;,
 -0.00598;0.16990;-0.21405;,
 -0.16327;0.16990;-0.14889;,
 -0.22842;0.16990;0.00840;,
 -0.24318;-0.07329;0.24559;,
 -0.00598;-0.07329;0.34384;,
 0.23121;-0.07329;0.24559;,
 0.32946;-0.07329;0.00840;,
 0.23121;-0.07329;-0.22880;,
 -0.00598;-0.07329;-0.32705;,
 -0.24318;-0.07329;-0.22880;,
 -0.34143;-0.07329;0.00840;,
 -0.24318;-0.07329;0.24559;,
 -0.16327;-0.16716;0.16568;,
 -0.00598;-0.16716;0.23084;,
 0.15131;-0.16716;0.16568;,
 0.21646;-0.16716;0.00840;,
 0.15131;-0.16716;-0.14889;,
 -0.00598;-0.16716;-0.21405;,
 -0.16327;-0.16716;-0.14889;,
 -0.22842;-0.16716;0.00840;,
 -0.16327;-0.16716;0.16568;,
 -0.11487;0.00000;-0.42566;,
 -2.13828;0.00000;-0.42566;,
 -2.13828;0.31612;-0.27894;,
 -0.11487;0.31612;-0.27894;,
 -0.11487;0.00000;0.42566;,
 -0.11487;0.27511;0.32378;,
 -2.13828;0.00000;0.05890;,
 -2.13828;0.27511;-0.04297;,
 -2.13828;0.00000;-0.42566;,
 -2.13828;0.31612;-0.27894;,
 -2.13828;0.27511;-0.04297;,
 -0.11487;0.27511;0.32378;,
 -2.13828;-0.27511;-0.04297;,
 -2.13828;-0.31612;-0.27894;,
 -0.11487;-0.31612;-0.27894;,
 -0.11487;-0.27511;0.32378;,
 -2.13828;-0.27511;-0.04297;,
 -2.13828;-0.31612;-0.27894;,
 -0.11487;-0.27511;0.32378;;
 
 90;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;21,18,20;,
 3;22,21,20;,
 3;23,22,20;,
 3;24,23,20;,
 3;25,24,20;,
 3;26,25,20;,
 3;19,26,20;,
 3;27,28,29;,
 3;28,30,29;,
 3;30,31,29;,
 3;31,32,29;,
 3;32,33,29;,
 3;33,34,29;,
 3;34,35,29;,
 3;35,27,29;,
 4;36,37,1,0;,
 4;37,38,4,1;,
 4;38,39,6,4;,
 4;39,40,8,6;,
 4;40,41,10,8;,
 4;41,42,12,10;,
 4;42,43,14,12;,
 4;43,44,16,14;,
 4;45,46,37,36;,
 4;46,47,38,37;,
 4;47,48,39,38;,
 4;48,49,40,39;,
 4;49,50,41,40;,
 4;50,51,42,41;,
 4;51,52,43,42;,
 4;52,53,44,43;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 3;72,73,74;,
 3;75,72,74;,
 3;76,75,74;,
 3;77,76,74;,
 3;78,77,74;,
 3;79,78,74;,
 3;80,79,74;,
 3;73,80,74;,
 3;81,82,83;,
 3;82,84,83;,
 3;84,85,83;,
 3;85,86,83;,
 3;86,87,83;,
 3;87,88,83;,
 3;88,89,83;,
 3;89,81,83;,
 4;90,91,55,54;,
 4;91,92,58,55;,
 4;92,93,60,58;,
 4;93,94,62,60;,
 4;94,95,64,62;,
 4;95,96,66,64;,
 4;96,97,68,66;,
 4;97,98,70,68;,
 4;99,100,91,90;,
 4;100,101,92,91;,
 4;101,102,93,92;,
 4;102,103,94,93;,
 4;103,104,95,94;,
 4;104,105,96,95;,
 4;105,106,97,96;,
 4;106,107,98,97;,
 4;108,109,110,111;,
 4;112,108,111,113;,
 4;114,112,113,115;,
 4;116,114,115,117;,
 4;110,118,119,111;,
 4;120,121,122,123;,
 4;124,114,116,125;,
 4;126,112,114,124;,
 4;122,108,112,126;,
 4;121,109,108,122;;
 
 MeshMaterialList {
  2;
  90;
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
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
  0;;
  Material {
   0.335686;0.335686;0.335686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  78;
  -0.268597;-0.925046;0.268598;,
  0.000003;-0.925043;0.379862;,
  0.268589;-0.925049;0.268599;,
  0.379838;-0.925053;-0.000003;,
  0.268590;-0.925050;-0.268591;,
  0.000004;-0.925052;-0.379842;,
  -0.268599;-0.925049;-0.268589;,
  -0.379860;-0.925044;-0.000003;,
  -0.276167;0.920578;0.276167;,
  0.000003;0.920575;0.390567;,
  0.276159;0.920579;0.276169;,
  0.390548;0.920583;-0.000004;,
  0.276164;0.920580;-0.276164;,
  0.000003;0.920582;-0.390550;,
  -0.276170;0.920579;-0.276161;,
  -0.390566;0.920575;-0.000003;,
  0.000001;-1.000000;-0.000001;,
  0.000001;1.000000;-0.000001;,
  -0.640789;0.422822;0.640789;,
  0.000003;0.422819;0.906214;,
  0.640781;0.422831;0.640791;,
  0.906206;0.422836;-0.000003;,
  0.640784;0.422837;-0.640784;,
  0.000002;0.422834;-0.906207;,
  -0.640791;0.422830;-0.640783;,
  -0.906214;0.422819;-0.000002;,
  -0.636880;-0.434473;0.636881;,
  0.000002;-0.434469;0.900687;,
  0.636872;-0.434484;0.636881;,
  0.900675;-0.434493;-0.000002;,
  0.636873;-0.434493;-0.636874;,
  0.000003;-0.434489;-0.900677;,
  -0.636881;-0.434484;-0.636872;,
  -0.900686;-0.434471;-0.000002;,
  -0.268591;-0.925050;0.268590;,
  0.000002;-0.925050;0.379845;,
  0.268602;-0.925045;0.268596;,
  0.379857;-0.925045;0.000004;,
  0.268604;-0.925046;-0.268591;,
  0.000001;-0.925050;-0.379845;,
  -0.268593;-0.925050;-0.268587;,
  -0.379838;-0.925053;0.000004;,
  -0.276163;0.920581;0.276162;,
  0.000003;0.920580;0.390554;,
  0.276175;0.920575;0.276169;,
  0.390565;0.920575;0.000004;,
  0.276176;0.920576;-0.276165;,
  0.000002;0.920580;-0.390555;,
  -0.276165;0.920581;-0.276159;,
  -0.390546;0.920584;0.000004;,
  0.000000;-1.000000;0.000002;,
  0.000000;1.000000;0.000002;,
  -0.640787;0.422819;0.640793;,
  0.000007;0.422814;0.906217;,
  0.640798;0.422803;0.640793;,
  0.906221;0.422804;0.000008;,
  0.640803;0.422805;-0.640787;,
  0.000006;0.422811;-0.906218;,
  -0.640792;0.422818;-0.640789;,
  -0.906211;0.422825;0.000008;,
  -0.636877;-0.434474;0.636883;,
  0.000006;-0.434470;0.900686;,
  0.636888;-0.434460;0.636882;,
  0.900692;-0.434459;0.000007;,
  0.636893;-0.434461;-0.636876;,
  0.000005;-0.434468;-0.900687;,
  -0.636882;-0.434473;-0.636879;,
  -0.900682;-0.434479;0.000007;,
  -0.006160;-0.992789;0.119718;,
  0.000000;0.420993;-0.907064;,
  1.000000;0.000000;0.000000;,
  -0.167573;0.342351;0.924508;,
  0.000000;0.000000;-1.000000;,
  -0.178350;0.000000;0.983967;,
  -1.000000;0.000000;0.000000;,
  -0.006160;0.992789;0.119718;,
  -0.167573;-0.342351;0.924508;,
  0.000000;-0.420993;-0.907064;;
  90;
  4;18,19,9,8;,
  4;19,20,10,9;,
  4;20,21,11,10;,
  4;21,22,12,11;,
  4;22,23,13,12;,
  4;23,24,14,13;,
  4;24,25,15,14;,
  4;25,18,8,15;,
  3;1,0,16;,
  3;2,1,16;,
  3;3,2,16;,
  3;4,3,16;,
  3;5,4,16;,
  3;6,5,16;,
  3;7,6,16;,
  3;0,7,16;,
  3;8,9,17;,
  3;9,10,17;,
  3;10,11,17;,
  3;11,12,17;,
  3;12,13,17;,
  3;13,14,17;,
  3;14,15,17;,
  3;15,8,17;,
  4;26,27,19,18;,
  4;27,28,20,19;,
  4;28,29,21,20;,
  4;29,30,22,21;,
  4;30,31,23,22;,
  4;31,32,24,23;,
  4;32,33,25,24;,
  4;33,26,18,25;,
  4;0,1,27,26;,
  4;1,2,28,27;,
  4;2,3,29,28;,
  4;3,4,30,29;,
  4;4,5,31,30;,
  4;5,6,32,31;,
  4;6,7,33,32;,
  4;7,0,26,33;,
  4;52,53,43,42;,
  4;53,54,44,43;,
  4;54,55,45,44;,
  4;55,56,46,45;,
  4;56,57,47,46;,
  4;57,58,48,47;,
  4;58,59,49,48;,
  4;59,52,42,49;,
  3;35,34,50;,
  3;36,35,50;,
  3;37,36,50;,
  3;38,37,50;,
  3;39,38,50;,
  3;40,39,50;,
  3;41,40,50;,
  3;34,41,50;,
  3;42,43,51;,
  3;43,44,51;,
  3;44,45,51;,
  3;45,46,51;,
  3;46,47,51;,
  3;47,48,51;,
  3;48,49,51;,
  3;49,42,51;,
  4;60,61,53,52;,
  4;61,62,54,53;,
  4;62,63,55,54;,
  4;63,64,56,55;,
  4;64,65,57,56;,
  4;65,66,58,57;,
  4;66,67,59,58;,
  4;67,60,52,59;,
  4;34,35,61,60;,
  4;35,36,62,61;,
  4;36,37,63,62;,
  4;37,38,64,63;,
  4;38,39,65,64;,
  4;39,40,66,65;,
  4;40,41,67,66;,
  4;41,34,60,67;,
  4;72,72,69,69;,
  4;70,70,70,70;,
  4;73,73,71,71;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;68,68,68,68;,
  4;74,74,74,74;,
  4;76,73,73,76;,
  4;70,70,70,70;,
  4;77,72,72,77;;
 }
 MeshTextureCoords {
  127;
  0.375000;0.442230;,
  0.406250;0.442230;,
  0.406250;0.311560;,
  0.375000;0.311560;,
  0.437500;0.442230;,
  0.437500;0.311560;,
  0.468750;0.442230;,
  0.468750;0.311560;,
  0.500000;0.442230;,
  0.500000;0.311560;,
  0.531250;0.442230;,
  0.531250;0.311560;,
  0.562500;0.442230;,
  0.562500;0.311560;,
  0.593750;0.442230;,
  0.593750;0.311560;,
  0.625000;0.442230;,
  0.625000;0.311560;,
  0.500000;1.000000;,
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
  0.656250;0.156250;,
  0.375000;0.560700;,
  0.406250;0.560700;,
  0.437500;0.560700;,
  0.468750;0.560700;,
  0.500000;0.560700;,
  0.531250;0.560700;,
  0.562500;0.560700;,
  0.593750;0.560700;,
  0.625000;0.560700;,
  0.375000;0.687500;,
  0.406250;0.687500;,
  0.437500;0.687500;,
  0.468750;0.687500;,
  0.500000;0.687500;,
  0.531250;0.687500;,
  0.562500;0.687500;,
  0.593750;0.687500;,
  0.625000;0.687500;,
  0.375000;0.442230;,
  0.406250;0.442230;,
  0.406250;0.311560;,
  0.375000;0.311560;,
  0.437500;0.442230;,
  0.437500;0.311560;,
  0.468750;0.442230;,
  0.468750;0.311560;,
  0.500000;0.442230;,
  0.500000;0.311560;,
  0.531250;0.442230;,
  0.531250;0.311560;,
  0.562500;0.442230;,
  0.562500;0.311560;,
  0.593750;0.442230;,
  0.593750;0.311560;,
  0.625000;0.442230;,
  0.625000;0.311560;,
  0.500000;1.000000;,
  0.610490;0.954240;,
  0.500000;0.850000;,
  0.389520;0.954240;,
  0.343750;0.843750;,
  0.389520;0.733270;,
  0.500000;0.687500;,
  0.610490;0.733270;,
  0.656250;0.843750;,
  0.610490;0.045760;,
  0.500000;0.000000;,
  0.500000;0.162500;,
  0.389520;0.045760;,
  0.343750;0.156250;,
  0.389520;0.266740;,
  0.500000;0.312500;,
  0.610490;0.266740;,
  0.656250;0.156250;,
  0.375000;0.560700;,
  0.406250;0.560700;,
  0.437500;0.560700;,
  0.468750;0.560700;,
  0.500000;0.560700;,
  0.531250;0.560700;,
  0.562500;0.560700;,
  0.593750;0.560700;,
  0.625000;0.560700;,
  0.375000;0.687500;,
  0.406250;0.687500;,
  0.437500;0.687500;,
  0.468750;0.687500;,
  0.500000;0.687500;,
  0.531250;0.687500;,
  0.562500;0.687500;,
  0.593750;0.687500;,
  0.625000;0.687500;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.500000;;
 }
}
