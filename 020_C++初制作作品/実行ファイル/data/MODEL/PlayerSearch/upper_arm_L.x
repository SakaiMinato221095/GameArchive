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
 22.70500;-5.45000;-4.99870;,
 10.45650;-8.19700;-5.69400;,
 10.30650;-0.64110;-7.63770;,
 22.55220;-1.62700;-6.94170;,
 -1.78870;-6.06180;-5.77090;,
 -1.97470;0.39560;-9.19180;,
 10.17070;6.11410;-5.83820;,
 22.46080;3.68000;-5.15490;,
 -2.15160;5.61590;-5.89280;,
 10.06790;6.88960;0.07960;,
 22.36160;4.46120;0.14260;,
 -2.25450;6.39140;0.02500;,
 10.01150;6.17410;5.60590;,
 22.31020;3.75320;4.84160;,
 -2.31080;5.67590;5.55120;,
 10.15700;-1.35300;7.04990;,
 22.41130;-2.32560;6.29840;,
 -2.15610;0.25970;7.72680;,
 10.29700;-8.14300;5.82080;,
 22.55410;-5.38270;5.06850;,
 -1.92210;-6.84500;5.73640;,
 10.40170;-8.92180;-0.01440;,
 22.65390;-7.43570;0.06050;,
 -1.81730;-7.62380;-0.09880;,
 -7.26550;0.15560;-0.22550;,
 25.53340;-0.31220;0.20430;;
 
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
    "data\\Texture\\UV_PlayerGomi.png";
   }
  }
 }
 MeshNormals {
  42;
  0.133061;-0.736753;-0.662940;,
  0.033990;-0.752856;-0.657307;,
  -0.383028;-0.711874;-0.588664;,
  0.081521;-0.033149;-0.996120;,
  0.062916;-0.005852;-0.998002;,
  0.043779;0.022129;-0.998796;,
  0.091989;0.288803;-0.952959;,
  0.077806;0.345727;-0.935104;,
  -0.332026;0.764556;-0.552460;,
  0.632220;0.774561;0.018786;,
  0.079086;0.996867;0.000940;,
  -0.040392;0.999183;-0.001321;,
  0.610904;0.751503;0.249077;,
  0.077763;0.987937;0.133919;,
  -0.040632;0.990956;0.127888;,
  0.078291;-0.032850;0.996389;,
  0.045915;-0.001431;0.998944;,
  0.013357;0.030076;0.999458;,
  0.479681;-0.613137;0.627670;,
  0.029930;-0.249935;0.967800;,
  -0.004047;-0.224175;0.974540;,
  0.179230;-0.983779;0.007446;,
  0.027724;-0.999528;-0.013256;,
  -0.404895;-0.901841;-0.150809;,
  -0.999812;0.019323;-0.001295;,
  0.997936;0.056987;0.029585;,
  0.619407;0.755809;-0.212337;,
  0.079004;0.988089;-0.132054;,
  0.088006;0.211511;0.973405;,
  0.059010;0.247200;0.967166;,
  0.029886;0.282356;0.958844;,
  0.034451;-0.980176;0.195109;,
  -0.556445;-0.791163;0.253831;,
  -0.864493;-0.393420;0.312846;,
  -0.938239;0.018867;0.345472;,
  -0.934437;0.017309;-0.355708;,
  -0.846402;0.427824;0.317127;,
  -0.882159;0.470861;0.009202;,
  0.963335;-0.267063;0.025735;,
  0.947283;0.054239;0.315775;,
  0.932616;-0.260304;-0.249937;,
  0.964087;0.054909;-0.259849;;
  24;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;26,27,10,9;,
  4;27,8,11,10;,
  4;9,10,13,12;,
  4;10,11,14,13;,
  4;28,29,16,15;,
  4;29,30,17,16;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;18,31,22,21;,
  4;31,32,23,22;,
  4;21,22,1,0;,
  4;22,23,2,1;,
  4;33,32,34,24;,
  4;2,23,24,35;,
  4;24,34,36,37;,
  4;35,24,37,8;,
  4;18,38,25,39;,
  4;38,40,41,25;,
  4;39,25,9,12;,
  4;25,41,26,9;;
 }
 MeshTextureCoords {
  26;
  0.420680;0.100630;,
  0.498010;0.101840;,
  0.498960;0.070100;,
  0.421640;0.068320;,
  0.575330;0.104510;,
  0.576500;0.063520;,
  0.499820;0.043450;,
  0.422220;0.050710;,
  0.577620;0.030390;,
  0.500470;0.038520;,
  0.422850;0.045750;,
  0.578270;0.025460;,
  0.500820;0.043070;,
  0.423170;0.050250;,
  0.578620;0.030000;,
  0.499900;0.074620;,
  0.422530;0.072750;,
  0.577640;0.064380;,
  0.499020;0.101500;,
  0.421630;0.100200;,
  0.576170;0.109480;,
  0.498360;0.106440;,
  0.421000;0.105190;,
  0.575510;0.114420;,
  0.609900;0.065040;,
  0.402820;0.068010;;
 }
}
