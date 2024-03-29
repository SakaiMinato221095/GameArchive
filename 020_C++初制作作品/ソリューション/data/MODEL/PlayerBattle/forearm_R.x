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
 26;
 -28.47026;-3.74129;4.54104;,
 -14.43313;-4.87683;5.52132;,
 -14.27237;0.80511;6.55266;,
 -28.36487;0.16181;5.58835;,
 -0.20580;-5.74133;6.41106;,
 -0.03885;0.19694;7.55559;,
 -14.17514;3.56717;5.81914;,
 -28.26288;3.07643;4.85345;,
 0.07679;3.43273;6.59316;,
 -14.11046;4.41752;0.30635;,
 -28.21168;3.93501;0.20384;,
 0.15397;4.34528;0.41237;,
 -14.09352;3.81209;-5.20733;,
 -28.21165;3.33984;-4.22131;,
 0.16359;3.52090;-5.07042;,
 -14.19184;0.00448;-6.45050;,
 -28.27374;0.69510;-5.47491;,
 0.06227;-0.61621;-6.76984;,
 -14.36788;-4.95929;-5.11504;,
 -28.41118;-3.03054;-4.15055;,
 -0.11781;-5.66009;-5.33501;,
 -14.41646;-5.37754;0.39197;,
 -28.29082;-4.22054;0.15330;,
 -0.18722;-6.57905;0.50813;,
 3.47008;0.03801;0.51608;,
 -30.68944;0.89337;0.14203;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;7,6,9,10;,
 4;6,8,11,9;,
 4;10,9,12,13;,
 4;9,11,14,12;,
 4;13,12,15,16;,
 4;12,14,17,15;,
 4;16,15,18,19;,
 4;15,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;22,21,1,0;,
 4;21,23,4,1;,
 4;23,20,17,24;,
 4;4,23,24,5;,
 4;24,17,14,11;,
 4;5,24,11,8;,
 4;19,22,25,16;,
 4;22,0,3,25;,
 4;16,25,10,13;,
 4;25,3,7,10;;
 
 MeshMaterialList {
  1;
  24;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\Texture\\UV_PlayerHero.png";
   }
  }
 }
 MeshNormals {
  54;
  -0.073619;-0.216504;0.973502;,
  -0.074144;-0.198974;0.977196;,
  -0.074646;-0.181381;0.980576;,
  -0.077051;0.018445;0.996856;,
  -0.071187;0.032570;0.996931;,
  -0.065317;0.046663;0.996773;,
  -0.076188;0.252365;0.964628;,
  -0.064386;0.262346;0.962824;,
  -0.052568;0.272263;0.960786;,
  -0.038787;0.998986;0.022863;,
  -0.015258;0.999746;0.016582;,
  0.008264;0.999913;0.010295;,
  -0.036889;0.991941;-0.121214;,
  -0.011582;0.992077;-0.125096;,
  0.013732;0.991563;-0.128897;,
  -0.082327;0.040944;-0.995764;,
  -0.047575;0.041427;-0.998008;,
  -0.013090;0.041855;-0.999038;,
  -0.091302;-0.293389;-0.951623;,
  -0.060971;-0.279646;-0.958165;,
  -0.030570;-0.265580;-0.963604;,
  -0.101685;-0.994222;-0.034379;,
  -0.087056;-0.996065;-0.016619;,
  -0.072416;-0.997374;0.001107;,
  0.999213;0.038242;0.010490;,
  -0.996502;0.083295;-0.006700;,
  -0.039878;0.985241;0.166464;,
  -0.018627;0.987277;0.157917;,
  0.002635;0.988791;0.149286;,
  -0.063982;0.370617;-0.926579;,
  -0.029188;0.358196;-0.933190;,
  0.005648;0.345270;-0.938487;,
  -0.115796;-0.978830;-0.168766;,
  -0.091539;-0.985550;-0.142518;,
  -0.067161;-0.990966;-0.116082;,
  -0.081187;-0.990669;0.109468;,
  -0.085693;-0.991225;0.100644;,
  -0.076672;-0.990016;0.118281;,
  0.944891;-0.327153;0.012357;,
  0.913754;-0.324911;-0.243898;,
  0.960290;0.038783;-0.276295;,
  0.913059;-0.307593;0.267788;,
  0.955190;0.034544;0.293972;,
  0.876718;0.397223;-0.271257;,
  0.916166;0.400734;0.007165;,
  0.883158;0.372553;0.285021;,
  -0.930595;-0.270423;-0.246708;,
  -0.962013;-0.272063;-0.022623;,
  -0.960397;0.087866;-0.264417;,
  -0.944173;-0.259772;0.202621;,
  -0.965664;0.073192;0.249269;,
  -0.902316;0.430954;0.010228;,
  -0.865758;0.434771;-0.247864;,
  -0.877550;0.397849;0.267625;;
  24;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;26,27,10,9;,
  4;27,28,11,10;,
  4;9,10,13,12;,
  4;10,11,14,13;,
  4;29,30,16,15;,
  4;30,31,17,16;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;32,33,22,21;,
  4;33,34,23,22;,
  4;21,22,35,36;,
  4;22,23,37,35;,
  4;38,39,40,24;,
  4;41,38,24,42;,
  4;24,40,43,44;,
  4;42,24,44,45;,
  4;46,47,25,48;,
  4;47,49,50,25;,
  4;48,25,51,52;,
  4;25,50,53,51;;
 }
 MeshTextureCoords {
  26;
  0.817596;0.071427;,
  0.741630;0.077605;,
  0.740760;0.046691;,
  0.817025;0.050191;,
  0.664635;0.082308;,
  0.663732;0.050000;,
  0.740234;0.031664;,
  0.816474;0.034334;,
  0.663106;0.032395;,
  0.739884;0.027037;,
  0.816197;0.029662;,
  0.662689;0.027430;,
  0.739793;0.030331;,
  0.816196;0.032901;,
  0.662636;0.031915;,
  0.740325;0.051047;,
  0.816532;0.047290;,
  0.663185;0.054424;,
  0.741277;0.078053;,
  0.817276;0.067560;,
  0.664159;0.081866;,
  0.741540;0.080329;,
  0.816625;0.074034;,
  0.664535;0.086866;,
  0.644743;0.050865;,
  0.829605;0.046211;;
 }
}
