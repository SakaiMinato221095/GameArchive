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
 5.63304;-18.01266;-10.71189;,
 2.77989;-17.99202;-14.22975;,
 2.84295;-16.90710;-14.22105;,
 5.69610;-16.92774;-10.70319;,
 0.00000;-17.97336;-15.71148;,
 0.00000;-16.88844;-15.70278;,
 -2.77989;-17.99202;-14.22975;,
 -2.84295;-16.90710;-14.22105;,
 -5.63304;-18.01266;-10.71189;,
 -5.69610;-16.92774;-10.70319;,
 2.89569;-15.31848;-14.21376;,
 5.74881;-15.33912;-10.69593;,
 0.00000;-15.29982;-15.69549;,
 -2.89569;-15.31848;-14.21376;,
 -5.74881;-15.33912;-10.69593;,
 2.94855;-13.73619;-14.20647;,
 5.80167;-13.75686;-10.68861;,
 0.00000;-13.71756;-15.68820;,
 -2.94855;-13.73619;-14.20647;,
 -5.80167;-13.75686;-10.68861;,
 3.03126;-12.11706;-11.15253;,
 5.38095;-12.36660;-9.00678;,
 0.00000;-11.50611;-12.68964;,
 -3.03126;-12.11706;-11.15253;,
 -5.38095;-12.36660;-9.00678;,
 2.80644;-10.81248;-5.73315;,
 5.70261;-10.83549;-3.53724;,
 0.00000;-10.79268;-5.78202;,
 -2.80644;-10.81248;-5.73315;,
 -5.70261;-10.83549;-3.53724;,
 2.10318;-0.06603;-4.18656;,
 4.64202;0.09042;-3.56574;,
 -0.21333;-0.02244;-4.39368;,
 -2.11074;-0.08067;-4.27884;,
 -4.53606;-0.13254;-3.60507;,
 2.10831;-0.23154;0.43947;,
 6.06570;0.06654;0.84369;,
 -0.00000;-0.19920;0.36822;,
 -2.10831;-0.23154;0.43947;,
 -6.01293;-0.14532;0.80433;,
 2.12910;0.05439;4.86741;,
 4.21062;0.00516;4.78617;,
 -0.00552;-0.05997;5.30400;,
 -2.04123;-0.04098;4.87245;,
 -4.24416;-0.22059;4.74687;,
 2.71290;-13.69635;6.08625;,
 5.18415;-13.73613;4.46565;,
 -0.00000;-13.67289;6.54972;,
 -2.71290;-13.69635;6.08625;,
 -5.18415;-13.73613;4.46565;,
 2.76603;-15.26592;6.07890;,
 5.23728;-15.30570;4.45833;,
 -0.00000;-15.24243;6.54240;,
 -2.76603;-15.26592;6.07890;,
 -5.23728;-15.30570;4.45833;,
 2.81823;-16.88007;6.07170;,
 5.28948;-16.91985;4.45110;,
 -0.00000;-16.85661;6.53520;,
 -2.81823;-16.88007;6.07170;,
 -5.28948;-16.91985;4.45110;,
 2.75571;-17.99016;6.06306;,
 5.17710;-18.03006;4.39746;,
 -0.00000;-17.96670;6.52656;,
 -2.75571;-17.99016;6.06306;,
 -5.17710;-18.03006;4.39746;,
 2.77989;-17.99202;0.43197;,
 6.30588;-18.02853;0.51237;,
 -0.00000;-17.96982;0.38307;,
 -2.77989;-17.99202;0.43197;,
 -6.30588;-18.02853;0.51237;,
 2.77989;-17.99202;-4.45527;,
 6.43848;-18.02532;-1.96044;,
 0.00000;-17.96982;-4.50414;,
 -2.77989;-17.99202;-4.45527;,
 -6.43848;-18.02532;-1.96044;,
 2.77989;-17.99202;-9.34251;,
 6.19353;-18.01998;-5.80857;,
 0.00000;-17.96982;-9.39138;,
 -2.77989;-17.99202;-9.34251;,
 -6.19353;-18.01998;-5.80857;,
 -6.36840;-16.91844;0.52101;,
 -6.50103;-16.91523;-1.95183;,
 -6.25659;-16.93506;-5.79987;,
 -6.31620;-15.30426;0.52821;,
 -6.44883;-15.30105;-1.94460;,
 -6.30933;-15.34644;-5.79258;,
 -6.26307;-13.73472;0.53553;,
 -6.39570;-13.73151;-1.93728;,
 -6.36219;-13.76418;-5.78529;,
 6.36840;-16.91844;0.52101;,
 6.50103;-16.91523;-1.95183;,
 6.25659;-16.93506;-5.79987;,
 6.31620;-15.30426;0.52821;,
 6.44883;-15.30105;-1.94460;,
 6.30933;-15.34644;-5.79258;,
 6.26307;-13.73472;0.53553;,
 6.39570;-13.73151;-1.93728;,
 6.36219;-13.76418;-5.78529;;
 
 96;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;12,13,18,17;,
 4;13,14,19,18;,
 4;16,15,20,21;,
 4;15,17,22,20;,
 4;17,18,23,22;,
 4;18,19,24,23;,
 4;21,20,25,26;,
 4;20,22,27,25;,
 4;22,23,28,27;,
 4;23,24,29,28;,
 4;26,25,30,31;,
 4;25,27,32,30;,
 4;27,28,33,32;,
 4;28,29,34,33;,
 4;31,30,35,36;,
 4;30,32,37,35;,
 4;32,33,38,37;,
 4;33,34,39,38;,
 4;36,35,40,41;,
 4;35,37,42,40;,
 4;37,38,43,42;,
 4;38,39,44,43;,
 4;41,40,45,46;,
 4;40,42,47,45;,
 4;42,43,48,47;,
 4;43,44,49,48;,
 4;46,45,50,51;,
 4;45,47,52,50;,
 4;47,48,53,52;,
 4;48,49,54,53;,
 4;51,50,55,56;,
 4;50,52,57,55;,
 4;52,53,58,57;,
 4;53,54,59,58;,
 4;56,55,60,61;,
 4;55,57,62,60;,
 4;57,58,63,62;,
 4;58,59,64,63;,
 4;61,60,65,66;,
 4;60,62,67,65;,
 4;62,63,68,67;,
 4;63,64,69,68;,
 4;66,65,70,71;,
 4;65,67,72,70;,
 4;67,68,73,72;,
 4;68,69,74,73;,
 4;71,70,75,76;,
 4;70,72,77,75;,
 4;72,73,78,77;,
 4;73,74,79,78;,
 4;76,75,1,0;,
 4;75,77,4,1;,
 4;77,78,6,4;,
 4;78,79,8,6;,
 4;69,64,59,80;,
 4;74,69,80,81;,
 4;79,74,81,82;,
 4;8,79,82,9;,
 4;80,59,54,83;,
 4;81,80,83,84;,
 4;82,81,84,85;,
 4;9,82,85,14;,
 4;83,54,49,86;,
 4;84,83,86,87;,
 4;85,84,87,88;,
 4;14,85,88,19;,
 4;86,49,44,39;,
 4;87,86,39,34;,
 4;88,87,34,29;,
 4;19,88,29,24;,
 4;61,66,89,56;,
 4;66,71,90,89;,
 4;71,76,91,90;,
 4;76,0,3,91;,
 4;56,89,92,51;,
 4;89,90,93,92;,
 4;90,91,94,93;,
 4;91,3,11,94;,
 4;51,92,95,46;,
 4;92,93,96,95;,
 4;93,94,97,96;,
 4;94,11,16,97;,
 4;46,95,36,41;,
 4;95,96,31,36;,
 4;96,97,26,31;,
 4;97,16,21,26;;
 
 MeshMaterialList {
  1;
  96;
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
  129;
  0.920713;-0.050413;-0.386971;,
  0.634067;-0.023678;-0.772916;,
  0.000000;-0.007160;-0.999974;,
  -0.634067;-0.023678;-0.772916;,
  -0.920713;-0.050413;-0.386971;,
  0.921187;-0.039615;-0.387097;,
  0.632555;-0.018576;-0.774293;,
  0.000000;-0.005537;-0.999985;,
  -0.632555;-0.018576;-0.774293;,
  -0.921187;-0.039615;-0.387097;,
  0.921552;-0.028906;-0.387178;,
  0.629589;-0.013488;-0.776812;,
  0.000000;-0.003860;-0.999992;,
  -0.629589;-0.013488;-0.776812;,
  -0.921552;-0.028906;-0.387178;,
  0.886233;0.288709;-0.362269;,
  0.583751;0.422398;-0.693408;,
  0.000000;-0.003801;-0.999993;,
  -0.583751;0.422398;-0.693408;,
  -0.886233;0.288709;-0.362269;,
  0.610666;0.735731;-0.292896;,
  0.316191;0.882405;-0.348403;,
  0.000000;0.934568;-0.355783;,
  -0.316191;0.882405;-0.348403;,
  -0.610666;0.735731;-0.292896;,
  0.658002;0.724387;-0.205663;,
  0.192458;0.959303;-0.206632;,
  0.000000;0.985520;-0.169557;,
  -0.192458;0.959303;-0.206632;,
  -0.658002;0.724387;-0.205663;,
  0.893663;0.118946;-0.432688;,
  0.243891;0.124153;-0.961823;,
  0.006762;0.133830;-0.990981;,
  -0.247732;0.120845;-0.961262;,
  -0.896595;0.121695;-0.425803;,
  -0.050182;0.998731;-0.004294;,
  -0.026614;0.999635;-0.004736;,
  -0.007027;0.999972;-0.002658;,
  -0.011194;0.999937;0.001147;,
  -0.011367;0.999932;0.002434;,
  -0.026085;0.998787;-0.041773;,
  -0.023488;0.998752;-0.044089;,
  -0.010813;0.999104;-0.040924;,
  -0.014376;0.999560;-0.025938;,
  -0.028014;0.999472;-0.016431;,
  0.753916;0.036625;0.655949;,
  0.305060;0.041071;0.951447;,
  -0.001418;0.046030;0.998939;,
  -0.309218;0.041393;0.950090;,
  -0.757166;0.037696;0.652134;,
  0.808307;0.024062;0.588269;,
  0.364705;0.006406;0.931101;,
  0.000000;-0.001818;0.999998;,
  -0.364705;0.006406;0.931101;,
  -0.808307;0.024062;0.588269;,
  0.808554;-0.028278;0.587742;,
  0.366204;-0.017108;0.930377;,
  0.000000;-0.007105;0.999975;,
  -0.366204;-0.017108;0.930377;,
  -0.808554;-0.028278;0.587742;,
  0.806631;-0.079807;0.585642;,
  0.368227;-0.040485;0.928854;,
  0.000000;-0.012411;0.999923;,
  -0.368227;-0.040485;0.928854;,
  -0.806631;-0.079807;0.585642;,
  -0.011497;-0.999933;-0.001243;,
  -0.009802;-0.999952;-0.000521;,
  0.000000;-1.000000;0.000200;,
  0.009802;-0.999952;-0.000521;,
  0.011497;-0.999933;-0.001243;,
  -0.009032;-0.999959;-0.000674;,
  -0.008509;-0.999964;-0.000337;,
  0.000000;-1.000000;-0.000000;,
  0.008509;-0.999964;-0.000337;,
  0.009032;-0.999959;-0.000674;,
  -0.007872;-0.999969;-0.000369;,
  -0.007807;-0.999970;-0.000114;,
  0.000000;-1.000000;0.000140;,
  0.007807;-0.999970;-0.000114;,
  0.007872;-0.999969;-0.000369;,
  -0.986630;-0.019526;0.161801;,
  -0.999792;-0.020359;-0.001557;,
  -0.995703;-0.036498;-0.085111;,
  -0.986599;0.031920;0.160012;,
  -0.999827;0.016450;0.008711;,
  -0.997056;-0.016248;-0.074936;,
  -0.990343;0.039074;0.133019;,
  -0.996344;0.064242;-0.056315;,
  -0.987313;0.125837;-0.096843;,
  0.986630;-0.019526;0.161801;,
  0.999792;-0.020359;-0.001557;,
  0.995703;-0.036498;-0.085111;,
  0.986599;0.031920;0.160012;,
  0.999827;0.016450;0.008711;,
  0.997056;-0.016248;-0.074936;,
  0.989941;0.037046;0.136547;,
  0.996454;0.061564;-0.057350;,
  0.987244;0.124486;-0.099257;,
  0.000000;0.843105;-0.537749;,
  0.796441;0.152738;-0.585109;,
  -0.805107;0.154258;-0.572718;,
  -0.074180;0.996692;0.033193;,
  -0.029702;0.998958;0.034663;,
  -0.003229;0.999360;0.035616;,
  -0.008003;0.999569;0.028230;,
  0.005287;0.999759;0.021298;,
  0.691212;0.048821;0.721001;,
  0.244287;0.074708;0.966821;,
  -0.002838;0.093943;0.995574;,
  -0.252649;0.075371;0.964618;,
  -0.698513;0.051020;0.713776;,
  -0.013287;-0.999910;-0.001560;,
  -0.010758;-0.999942;-0.000579;,
  0.000000;-1.000000;0.000401;,
  0.010758;-0.999942;-0.000579;,
  0.013287;-0.999910;-0.001560;,
  -0.007442;-0.999972;-0.000018;,
  -0.007386;-0.999973;-0.000315;,
  0.000000;-1.000000;0.000280;,
  0.007442;-0.999972;-0.000018;,
  0.007386;-0.999973;-0.000315;,
  -0.984096;-0.070216;0.163171;,
  -0.998382;-0.056650;-0.004940;,
  -0.994473;-0.056655;-0.088391;,
  -0.993395;0.045617;0.105286;,
  0.984096;-0.070216;0.163171;,
  0.998382;-0.056650;-0.004940;,
  0.994473;-0.056655;-0.088391;,
  0.992790;0.041524;0.112441;;
  96;
  4;0,1,6,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;5,6,11,10;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;10,11,16,15;,
  4;11,12,17,16;,
  4;12,13,18,17;,
  4;13,14,19,18;,
  4;15,16,21,20;,
  4;16,98,22,21;,
  4;98,18,23,22;,
  4;18,19,24,23;,
  4;20,21,26,25;,
  4;21,22,27,26;,
  4;22,23,28,27;,
  4;23,24,29,28;,
  4;99,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,100,34,33;,
  4;101,102,36,35;,
  4;102,103,37,36;,
  4;103,104,38,37;,
  4;104,105,39,38;,
  4;35,36,41,40;,
  4;36,37,42,41;,
  4;37,38,43,42;,
  4;38,39,44,43;,
  4;106,107,46,45;,
  4;107,108,47,46;,
  4;108,109,48,47;,
  4;109,110,49,48;,
  4;45,46,51,50;,
  4;46,47,52,51;,
  4;47,48,53,52;,
  4;48,49,54,53;,
  4;50,51,56,55;,
  4;51,52,57,56;,
  4;52,53,58,57;,
  4;53,54,59,58;,
  4;55,56,61,60;,
  4;56,57,62,61;,
  4;57,58,63,62;,
  4;58,59,64,63;,
  4;111,112,66,65;,
  4;112,113,67,66;,
  4;113,114,68,67;,
  4;114,115,69,68;,
  4;65,66,71,70;,
  4;66,67,72,71;,
  4;67,68,73,72;,
  4;68,69,74,73;,
  4;70,71,76,75;,
  4;71,72,77,76;,
  4;72,73,78,77;,
  4;73,74,79,78;,
  4;75,76,116,117;,
  4;76,77,118,116;,
  4;77,78,119,118;,
  4;78,79,120,119;,
  4;121,64,59,80;,
  4;122,121,80,81;,
  4;123,122,81,82;,
  4;4,123,82,9;,
  4;80,59,54,83;,
  4;81,80,83,84;,
  4;82,81,84,85;,
  4;9,82,85,14;,
  4;83,54,49,86;,
  4;84,83,86,87;,
  4;85,84,87,88;,
  4;14,85,88,19;,
  4;86,49,110,124;,
  4;87,86,124,34;,
  4;88,87,34,100;,
  4;19,88,29,24;,
  4;60,125,89,55;,
  4;125,126,90,89;,
  4;126,127,91,90;,
  4;127,0,5,91;,
  4;55,89,92,50;,
  4;89,90,93,92;,
  4;90,91,94,93;,
  4;91,5,10,94;,
  4;50,92,95,45;,
  4;92,93,96,95;,
  4;93,94,97,96;,
  4;94,10,15,97;,
  4;45,95,128,106;,
  4;95,96,30,128;,
  4;96,97,99,30;,
  4;97,15,20,25;;
 }
 MeshTextureCoords {
  98;
  0.158429;0.214358;,
  0.172834;0.214227;,
  0.172516;0.207341;,
  0.158110;0.207472;,
  0.190523;0.214109;,
  0.190523;0.207223;,
  0.208212;0.214227;,
  0.208530;0.207341;,
  0.222617;0.214358;,
  0.222936;0.207472;,
  0.172249;0.197257;,
  0.157844;0.197388;,
  0.190523;0.197139;,
  0.208797;0.197257;,
  0.223202;0.197388;,
  0.171982;0.187214;,
  0.157577;0.187345;,
  0.190523;0.187095;,
  0.209064;0.187214;,
  0.223469;0.187345;,
  0.171565;0.176936;,
  0.159701;0.178520;,
  0.190523;0.173058;,
  0.209481;0.176936;,
  0.221345;0.178520;,
  0.172700;0.168656;,
  0.158078;0.168802;,
  0.190523;0.168530;,
  0.208346;0.168656;,
  0.222968;0.168802;,
  0.176251;0.074176;,
  0.163432;0.073183;,
  0.190060;0.073900;,
  0.204834;0.074269;,
  0.217079;0.074599;,
  0.176225;0.075227;,
  0.156244;0.073335;,
  0.190523;0.075022;,
  0.204821;0.075227;,
  0.224535;0.074680;,
  0.176120;0.073412;,
  0.165610;0.073725;,
  0.190396;0.074138;,
  0.204483;0.074018;,
  0.215605;0.075158;,
  0.173172;0.186961;,
  0.160695;0.187213;,
  0.190523;0.186812;,
  0.207874;0.186961;,
  0.220351;0.187213;,
  0.172904;0.196924;,
  0.160427;0.197176;,
  0.190523;0.196775;,
  0.208142;0.196924;,
  0.220619;0.197176;,
  0.172640;0.207169;,
  0.160163;0.207422;,
  0.190523;0.207020;,
  0.208406;0.207169;,
  0.220883;0.207422;,
  0.172956;0.214216;,
  0.160731;0.214469;,
  0.190523;0.214067;,
  0.208090;0.214216;,
  0.220315;0.214469;,
  0.172834;0.214227;,
  0.155032;0.214459;,
  0.190523;0.214086;,
  0.208212;0.214227;,
  0.226014;0.214459;,
  0.172834;0.214227;,
  0.154362;0.214438;,
  0.190523;0.214086;,
  0.208212;0.214227;,
  0.226684;0.214438;,
  0.172834;0.214227;,
  0.155599;0.214405;,
  0.190523;0.214086;,
  0.208212;0.214227;,
  0.225447;0.214405;,
  0.226330;0.207413;,
  0.227000;0.207393;,
  0.225766;0.207518;,
  0.226066;0.197167;,
  0.226736;0.197146;,
  0.226032;0.197435;,
  0.225798;0.187204;,
  0.226468;0.187184;,
  0.226299;0.187391;,
  0.154716;0.207413;,
  0.154046;0.207393;,
  0.155281;0.207518;,
  0.154980;0.197167;,
  0.154310;0.197146;,
  0.155014;0.197435;,
  0.155248;0.187204;,
  0.154578;0.187184;,
  0.154747;0.187391;;
 }
}
