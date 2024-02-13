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
 192;
 0.34840;-0.31085;-0.68694;,
 0.53666;-0.31085;-0.48466;,
 0.46680;-2.81303;-0.40011;,
 0.40985;-2.81303;-0.47642;,
 0.40985;-2.81303;0.62896;,
 0.52476;-2.81303;0.54186;,
 0.59462;-0.31085;0.63281;,
 0.28675;-0.31085;0.82288;,
 0.67182;-2.81303;0.07182;,
 0.55647;-2.81303;0.44053;,
 0.40985;-2.81303;0.50885;,
 0.40985;-2.81303;0.07182;,
 0.76913;-0.31085;0.07502;,
 0.63224;-0.31085;0.51257;,
 0.55647;-2.81303;0.44053;,
 0.67182;-2.81303;0.07182;,
 -0.36268;-0.31085;0.51257;,
 -0.46795;-0.31085;0.07502;,
 -0.37064;-2.81303;0.07182;,
 -0.28193;-2.81303;0.44053;,
 0.01961;-2.81303;0.07182;,
 0.06396;-2.81303;0.56621;,
 0.07615;-2.81303;0.70208;,
 0.40985;-2.81303;0.62896;,
 0.28675;-0.31085;0.82288;,
 0.06225;-0.31085;0.82294;,
 0.28675;-0.31085;0.68035;,
 0.45825;-0.31085;0.07502;,
 -0.00485;-0.31085;0.07502;,
 0.04778;-0.31085;0.66171;,
 0.05828;-0.31085;-0.78020;,
 0.34840;-0.31085;-0.68694;,
 0.40985;-2.81303;-0.47642;,
 0.07218;-2.81303;-0.65933;,
 0.55836;0.45191;0.57034;,
 0.63910;0.45191;0.07502;,
 0.45825;-0.31085;0.07502;,
 0.28675;-0.31085;0.68035;,
 0.35398;0.45191;-0.59414;,
 0.63910;0.45191;0.07502;,
 0.55836;0.45191;0.57034;,
 0.29385;0.45191;0.71952;,
 0.34840;-0.31085;-0.56103;,
 0.04926;-0.31085;-0.56093;,
 0.51101;0.45191;-0.39353;,
 0.34840;-0.31085;-0.56103;,
 0.51101;0.45191;-0.39353;,
 0.62840;-0.31085;-0.37482;,
 0.55323;-2.81303;-0.30725;,
 0.55323;-2.81303;-0.30725;,
 0.40985;-2.81303;-0.37031;,
 0.06521;-2.81303;-0.46408;,
 -0.35972;-0.31085;-0.37482;,
 -0.27944;-2.81303;-0.30725;,
 -0.37064;-2.81303;0.07182;,
 -0.27944;-2.81303;-0.30725;,
 -0.28193;-2.81303;0.44053;,
 -0.33375;-0.31085;0.63281;,
 -0.25755;-2.81303;0.54186;,
 -0.46795;-0.31085;0.07502;,
 -0.36268;-0.31085;0.51257;,
 -0.35972;-0.31085;-0.37482;,
 -0.21349;-2.81303;-0.40139;,
 -0.28969;-0.31085;-0.48595;,
 0.05828;-0.31085;-0.78020;,
 0.07218;-2.81303;-0.65933;,
 -0.28969;-0.31085;-0.48595;,
 0.05828;-0.31085;-0.78020;,
 0.34840;-0.31085;-0.68694;,
 0.35398;0.45191;-0.59414;,
 0.34840;-0.31085;-0.68694;,
 0.40985;-2.81303;-0.47642;,
 0.46680;-2.81303;-0.40011;,
 0.07218;-2.81303;-0.65933;,
 -0.21349;-2.81303;-0.40139;,
 -0.25755;-2.81303;0.54186;,
 0.07615;-2.81303;0.70208;,
 0.40985;-2.81303;0.62896;,
 0.52476;-2.81303;0.54186;,
 0.28675;-0.31085;0.82288;,
 0.29385;0.45191;0.71952;,
 0.06225;-0.31085;0.82294;,
 0.28675;-0.31085;0.82288;,
 -0.33375;-0.31085;0.63281;,
 -0.25755;-2.81303;0.54186;,
 -0.33375;-0.31085;0.63281;,
 0.46638;0.30583;-0.35543;,
 0.39040;0.27312;-0.46267;,
 0.24466;0.43524;-0.46267;,
 0.27110;0.50112;-0.35543;,
 0.24466;0.43524;-0.46267;,
 0.00433;-0.01743;-0.46267;,
 0.00433;0.49458;-0.46267;,
 -0.23601;0.43524;-0.46267;,
 -0.38175;0.27312;-0.46267;,
 -0.45773;0.30583;-0.35543;,
 -0.38175;0.27312;-0.46267;,
 -0.43509;0.05166;-0.46267;,
 -0.52921;0.03906;-0.35543;,
 -0.38175;-0.16979;-0.46267;,
 -0.45773;-0.22771;-0.35543;,
 -0.23132;-0.35763;-0.46267;,
 -0.30356;-0.41091;-0.35543;,
 -0.30356;-0.41091;-0.35543;,
 -0.23132;-0.35763;-0.46267;,
 0.00433;-0.39125;-0.46267;,
 0.00433;-0.49448;-0.35543;,
 0.23998;-0.35763;-0.46267;,
 0.31222;-0.41091;-0.35543;,
 0.31222;-0.41091;-0.35543;,
 0.23998;-0.35763;-0.46267;,
 0.39040;-0.16979;-0.46267;,
 0.46638;-0.22771;-0.35543;,
 0.44375;0.05166;-0.46267;,
 0.53786;0.03906;-0.35543;,
 0.27110;0.50112;-0.35543;,
 0.24466;0.43524;-0.46267;,
 0.00433;0.49458;-0.46267;,
 0.00433;0.57260;-0.35543;,
 -0.23601;0.43524;-0.46267;,
 -0.26244;0.50112;-0.35543;,
 0.44375;0.05166;-0.46267;,
 0.39040;0.27312;-0.46267;,
 0.39040;-0.16979;-0.46267;,
 0.23998;-0.35763;-0.46267;,
 0.00433;-0.39125;-0.46267;,
 -0.23132;-0.35763;-0.46267;,
 -0.38175;-0.16979;-0.46267;,
 -0.43509;0.05166;-0.46267;,
 -0.26244;0.50112;-0.35543;,
 -0.23601;0.43524;-0.46267;,
 0.46638;0.30583;0.04608;,
 0.27110;0.50112;0.04608;,
 0.27110;0.50112;0.04608;,
 0.00433;0.57260;0.04608;,
 -0.26244;0.50112;0.04608;,
 -0.26244;0.50112;0.04608;,
 -0.45773;0.30583;0.04608;,
 -0.52921;0.03906;0.04608;,
 -0.45773;-0.22771;0.04608;,
 -0.30356;-0.41091;0.04608;,
 -0.30356;-0.41091;0.04608;,
 0.00433;-0.49448;0.04608;,
 0.31222;-0.41091;0.04608;,
 0.31222;-0.41091;0.04608;,
 0.46638;-0.22771;0.04608;,
 0.53786;0.03906;0.04608;,
 0.46638;0.30583;0.44758;,
 0.27110;0.50112;0.44758;,
 0.24466;0.43524;0.55483;,
 0.39040;0.27312;0.55483;,
 0.24466;0.43524;0.55483;,
 0.00433;0.49458;0.55483;,
 0.00433;-0.01743;0.55483;,
 -0.23601;0.43524;0.55483;,
 -0.38175;0.27312;0.55483;,
 -0.45773;0.30583;0.44758;,
 -0.52921;0.03906;0.44758;,
 -0.43509;0.05166;0.55483;,
 -0.38175;0.27312;0.55483;,
 -0.45773;-0.22771;0.44758;,
 -0.38175;-0.16979;0.55483;,
 -0.30356;-0.41091;0.44758;,
 -0.24801;-0.32808;0.55483;,
 -0.30356;-0.41091;0.44758;,
 0.00433;-0.49448;0.44758;,
 0.00433;-0.39125;0.55483;,
 -0.24801;-0.32808;0.55483;,
 0.31222;-0.41091;0.44758;,
 0.25667;-0.32808;0.55483;,
 0.31222;-0.41091;0.44758;,
 0.46638;-0.22771;0.44758;,
 0.39040;-0.16979;0.55483;,
 0.25667;-0.32808;0.55483;,
 0.53786;0.03906;0.44758;,
 0.44375;0.05166;0.55483;,
 0.27110;0.50112;0.44758;,
 0.00433;0.57260;0.44758;,
 0.00433;0.49458;0.55483;,
 0.24466;0.43524;0.55483;,
 -0.26244;0.50112;0.44758;,
 -0.23601;0.43524;0.55483;,
 0.44375;0.05166;0.55483;,
 0.39040;0.27312;0.55483;,
 0.39040;-0.16979;0.55483;,
 0.25667;-0.32808;0.55483;,
 0.00433;-0.39125;0.55483;,
 -0.24801;-0.32808;0.55483;,
 -0.38175;-0.16979;0.55483;,
 -0.43509;0.05166;0.55483;,
 -0.26244;0.50112;0.44758;,
 -0.23601;0.43524;0.55483;;
 
 116;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,11,10,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 3;0,38,1;,
 4;39,40,13,12;,
 3;6,41,7;,
 4;28,27,42,43;,
 4;35,44,45,36;,
 4;46,39,12,47;,
 4;47,12,15,48;,
 4;49,8,11,50;,
 4;50,11,20,51;,
 4;17,52,53,18;,
 4;54,55,51,20;,
 4;56,54,20,21;,
 4;57,58,22,25;,
 4;59,60,29,28;,
 4;61,59,28,43;,
 4;62,63,64,65;,
 4;66,61,43,67;,
 4;42,68,67,43;,
 4;44,69,70,45;,
 4;1,38,46,47;,
 4;2,1,47,48;,
 4;71,72,49,50;,
 4;73,71,50,51;,
 4;55,74,73,51;,
 4;52,63,62,53;,
 4;75,56,21,76;,
 4;10,77,76,21;,
 4;9,78,77,10;,
 4;13,6,5,14;,
 4;40,41,6,13;,
 4;79,80,34,37;,
 4;81,82,26,29;,
 4;60,83,81,29;,
 4;84,85,16,19;,
 4;86,87,88,89;,
 3;90,91,92;,
 3;92,91,93;,
 3;93,91,94;,
 4;95,96,97,98;,
 4;98,97,99,100;,
 4;100,99,101,102;,
 4;103,104,105,106;,
 4;106,105,107,108;,
 4;109,110,111,112;,
 4;112,111,113,114;,
 4;114,113,87,86;,
 4;115,116,117,118;,
 4;118,117,119,120;,
 3;121,91,122;,
 3;123,91,121;,
 3;124,91,123;,
 3;125,91,124;,
 3;126,91,125;,
 3;127,91,126;,
 3;128,91,127;,
 3;94,91,128;,
 4;129,130,96,95;,
 3;122,91,90;,
 4;131,86,89,132;,
 4;133,115,118,134;,
 4;134,118,120,135;,
 4;136,129,95,137;,
 4;137,95,98,138;,
 4;138,98,100,139;,
 4;139,100,102,140;,
 4;141,103,106,142;,
 4;142,106,108,143;,
 4;144,109,112,145;,
 4;145,112,114,146;,
 4;146,114,86,131;,
 4;147,148,149,150;,
 3;151,152,153;,
 3;152,154,153;,
 3;154,155,153;,
 4;156,157,158,159;,
 4;157,160,161,158;,
 4;160,162,163,161;,
 4;164,165,166,167;,
 4;165,168,169,166;,
 4;170,171,172,173;,
 4;171,174,175,172;,
 4;174,147,150,175;,
 4;176,177,178,179;,
 4;177,180,181,178;,
 3;182,183,153;,
 3;184,182,153;,
 3;185,184,153;,
 3;186,185,153;,
 3;187,186,153;,
 3;188,187,153;,
 3;189,188,153;,
 3;155,189,153;,
 4;190,156,159,191;,
 3;183,151,153;,
 4;131,132,148,147;,
 4;133,134,177,176;,
 4;134,135,180,177;,
 4;136,137,156,190;,
 4;137,138,157,156;,
 4;138,139,160,157;,
 4;139,140,162,160;,
 4;141,142,165,164;,
 4;142,143,168,165;,
 4;144,145,171,170;,
 4;145,146,174,171;,
 4;146,131,147,174;;
 
 MeshMaterialList {
  1;
  116;
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
    "data\\TEXTURE\\MATERIAL\\acTex002.png";
   }
  }
 }
 MeshNormals {
  95;
  -0.751328;-0.043230;-0.658511;,
  0.758359;-0.041359;-0.650523;,
  0.756912;0.023898;-0.653080;,
  -0.777008;-0.046482;0.627772;,
  0.735010;0.030657;0.677363;,
  0.803418;-0.042564;0.593892;,
  0.596202;-0.048555;-0.801365;,
  0.346626;-0.051529;0.936587;,
  0.409332;0.003359;0.912379;,
  0.645105;-0.005847;-0.764072;,
  0.657701;0.100356;0.746564;,
  0.752230;0.089089;-0.652850;,
  -0.999245;-0.038862;-0.000003;,
  0.000000;1.000000;0.000000;,
  -0.972332;0.233597;0.001798;,
  0.998567;0.051909;-0.012986;,
  0.000000;-1.000000;-0.000000;,
  0.392245;-0.053433;-0.918307;,
  -0.168865;-0.053482;0.984187;,
  -0.915810;-0.040743;-0.399540;,
  -0.956392;0.109562;0.270759;,
  0.877647;0.044310;-0.477255;,
  0.870614;-0.040092;-0.490331;,
  -0.971554;-0.038083;0.233737;,
  0.928620;0.034475;0.369428;,
  -0.919694;0.149454;-0.363079;,
  0.823436;0.469581;-0.318508;,
  0.479865;0.823709;-0.302048;,
  -0.000000;0.953024;-0.302895;,
  -0.479864;0.823710;-0.302047;,
  -0.823436;0.469582;-0.318507;,
  -0.938003;0.001555;-0.346623;,
  -0.831529;-0.427688;-0.354460;,
  -0.493387;-0.794145;-0.354828;,
  -0.000000;-0.941010;-0.338378;,
  0.493387;-0.794145;-0.354828;,
  0.831529;-0.427688;-0.354460;,
  0.938003;0.001555;-0.346623;,
  0.000000;0.000000;-1.000000;,
  0.231074;0.392371;-0.890309;,
  -0.000000;0.456507;-0.889720;,
  -0.231074;0.392372;-0.890308;,
  0.385393;0.216431;-0.897012;,
  0.416887;0.001581;-0.908957;,
  0.365525;-0.184599;-0.912313;,
  0.208393;-0.347763;-0.914130;,
  -0.000000;-0.426868;-0.904314;,
  -0.208393;-0.347763;-0.914130;,
  -0.365524;-0.184599;-0.912313;,
  -0.416887;0.001581;-0.908957;,
  -0.385393;0.216431;-0.897011;,
  0.866025;0.500001;0.000000;,
  0.500000;0.866025;0.000000;,
  -0.000000;1.000000;0.000000;,
  -0.499999;0.866026;0.000000;,
  -0.866024;0.500002;0.000000;,
  -1.000000;0.000001;0.000000;,
  -0.886687;-0.462370;0.000000;,
  -0.538068;-0.842902;0.000000;,
  0.538068;-0.842902;-0.000000;,
  0.886687;-0.462370;-0.000000;,
  1.000000;0.000001;0.000000;,
  0.823436;0.469581;0.318508;,
  0.479865;0.823709;0.302048;,
  -0.000000;0.953024;0.302895;,
  -0.479864;0.823710;0.302047;,
  -0.823436;0.469582;0.318507;,
  -0.938003;0.001555;0.346623;,
  -0.829221;-0.428777;0.358528;,
  -0.497841;-0.782930;0.373061;,
  0.000000;-0.928635;0.370995;,
  0.497841;-0.782930;0.373061;,
  0.829221;-0.428777;0.358528;,
  0.938003;0.001555;0.346623;,
  0.000000;0.000000;1.000000;,
  0.231074;0.392371;0.890309;,
  -0.000000;0.456507;0.889720;,
  -0.231074;0.392372;0.890308;,
  0.385393;0.216431;0.897012;,
  0.416887;0.001581;0.908957;,
  0.360872;-0.184513;0.914181;,
  0.208955;-0.330346;0.920440;,
  0.000000;-0.393989;0.919115;,
  -0.208955;-0.330346;0.920440;,
  -0.360872;-0.184513;0.914181;,
  -0.416887;0.001581;0.908957;,
  -0.385393;0.216431;0.897011;,
  0.953711;-0.037472;0.298380;,
  0.999245;-0.038862;-0.000004;,
  0.989670;0.141046;-0.025688;,
  0.892421;0.107864;0.438120;,
  0.878241;0.128177;-0.460721;,
  -0.657406;-0.042947;-0.752312;,
  -0.945189;0.021061;0.325845;,
  -0.863168;0.033899;-0.503777;;
  116;
  4;9,2,1,6;,
  4;7,5,4,8;,
  4;16,16,16,16;,
  4;15,24,87,88;,
  4;23,12,12,23;,
  4;16,16,16,16;,
  4;18,7,8,18;,
  4;13,13,13,13;,
  4;17,9,6,17;,
  4;25,14,14,25;,
  3;9,11,2;,
  4;89,90,24,15;,
  3;4,10,8;,
  4;13,13,13,13;,
  4;14,20,20,14;,
  4;91,89,15,21;,
  4;21,15,88,22;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;12,19,19,12;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;3,3,18,18;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;0,0,92,92;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;20,93,93,20;,
  4;2,11,91,21;,
  4;1,2,21,22;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;19,0,0,19;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;24,4,5,87;,
  4;90,10,4,24;,
  4;94,94,25,25;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;3,3,23,23;,
  4;26,42,39,27;,
  3;39,38,40;,
  3;40,38,41;,
  3;41,38,50;,
  4;30,50,49,31;,
  4;31,49,48,32;,
  4;32,48,47,33;,
  4;33,47,46,34;,
  4;34,46,45,35;,
  4;35,45,44,36;,
  4;36,44,43,37;,
  4;37,43,42,26;,
  4;27,39,40,28;,
  4;28,40,41,29;,
  3;43,38,42;,
  3;44,38,43;,
  3;45,38,44;,
  3;46,38,45;,
  3;47,38,46;,
  3;48,38,47;,
  3;49,38,48;,
  3;50,38,49;,
  4;29,41,50,30;,
  3;42,38,39;,
  4;51,26,27,52;,
  4;52,27,28,53;,
  4;53,28,29,54;,
  4;54,29,30,55;,
  4;55,30,31,56;,
  4;56,31,32,57;,
  4;57,32,33,58;,
  4;58,33,34,16;,
  4;16,34,35,59;,
  4;59,35,36,60;,
  4;60,36,37,61;,
  4;61,37,26,51;,
  4;62,63,75,78;,
  3;75,76,74;,
  3;76,77,74;,
  3;77,86,74;,
  4;66,67,85,86;,
  4;67,68,84,85;,
  4;68,69,83,84;,
  4;69,70,82,83;,
  4;70,71,81,82;,
  4;71,72,80,81;,
  4;72,73,79,80;,
  4;73,62,78,79;,
  4;63,64,76,75;,
  4;64,65,77,76;,
  3;79,78,74;,
  3;80,79,74;,
  3;81,80,74;,
  3;82,81,74;,
  3;83,82,74;,
  3;84,83,74;,
  3;85,84,74;,
  3;86,85,74;,
  4;65,66,86,77;,
  3;78,75,74;,
  4;51,52,63,62;,
  4;52,53,64,63;,
  4;53,54,65,64;,
  4;54,55,66,65;,
  4;55,56,67,66;,
  4;56,57,68,67;,
  4;57,58,69,68;,
  4;58,16,70,69;,
  4;16,59,71,70;,
  4;59,60,72,71;,
  4;60,61,73,72;,
  4;61,51,62,73;;
 }
 MeshTextureCoords {
  192;
  0.121530;0.115110;,
  0.108110;0.115110;,
  0.102500;0.281100;,
  0.120940;0.281100;,
  0.022450;0.281290;,
  0.040020;0.281100;,
  0.033980;0.115110;,
  0.021380;0.115110;,
  0.126070;0.342400;,
  0.118840;0.365490;,
  0.109660;0.369770;,
  0.109660;0.342400;,
  0.070990;0.115110;,
  0.041960;0.115110;,
  0.046740;0.281100;,
  0.071200;0.281100;,
  0.226000;0.115520;,
  0.196970;0.115520;,
  0.196760;0.281500;,
  0.221220;0.281500;,
  0.085230;0.342400;,
  0.088000;0.373360;,
  0.258150;0.114330;,
  0.280290;0.114330;,
  0.272120;0.280320;,
  0.257230;0.280320;,
  0.190410;0.299370;,
  0.199220;0.330450;,
  0.175450;0.330450;,
  0.178150;0.300330;,
  0.139940;0.115040;,
  0.120690;0.115040;,
  0.121400;0.281020;,
  0.147990;0.281480;,
  0.157140;0.065510;,
  0.188010;0.065730;,
  0.187680;0.113270;,
  0.149950;0.113010;,
  0.115380;0.064510;,
  0.070990;0.064510;,
  0.038130;0.064510;,
  0.028230;0.064510;,
  0.193580;0.363100;,
  0.178220;0.363090;,
  0.217220;0.065930;,
  0.227330;0.113540;,
  0.102070;0.064510;,
  0.100830;0.115110;,
  0.096340;0.281100;,
  0.118640;0.318670;,
  0.109660;0.314720;,
  0.088080;0.308850;,
  0.167130;0.115520;,
  0.171610;0.281500;,
  0.060790;0.342400;,
  0.066500;0.318670;,
  0.066350;0.365490;,
  0.230960;0.280320;,
  0.236010;0.114330;,
  0.151670;0.330450;,
  0.157080;0.307990;,
  0.157230;0.353540;,
  0.165370;0.281500;,
  0.159760;0.115520;,
  0.140240;0.115520;,
  0.148260;0.281500;,
  0.160820;0.359240;,
  0.178690;0.374350;,
  0.193580;0.369560;,
  0.229720;0.066010;,
  0.235180;0.113590;,
  0.109660;0.308080;,
  0.113230;0.312850;,
  0.088520;0.296620;,
  0.070630;0.312770;,
  0.067870;0.371830;,
  0.088770;0.381870;,
  0.109660;0.377290;,
  0.116860;0.371830;,
  0.141070;0.112950;,
  0.147840;0.065450;,
  0.178890;0.292050;,
  0.190410;0.292060;,
  0.158560;0.301810;,
  0.227940;0.281500;,
  0.233970;0.115520;,
  0.290850;0.042270;,
  0.288720;0.035310;,
  0.299250;0.035310;,
  0.303530;0.042270;,
  0.278070;0.301930;,
  0.257110;0.341400;,
  0.257110;0.296750;,
  0.236150;0.301930;,
  0.223440;0.316060;,
  0.291310;0.093170;,
  0.289180;0.100140;,
  0.274800;0.100140;,
  0.273980;0.093170;,
  0.260410;0.100140;,
  0.256650;0.093170;,
  0.248220;0.100140;,
  0.244760;0.093170;,
  0.255590;0.041140;,
  0.260280;0.034180;,
  0.275580;0.034180;,
  0.275580;0.041140;,
  0.290890;0.034180;,
  0.295580;0.041140;,
  0.244300;0.042270;,
  0.247760;0.035310;,
  0.259960;0.035310;,
  0.256200;0.042270;,
  0.274340;0.035310;,
  0.273520;0.042270;,
  0.292020;0.094130;,
  0.290310;0.101090;,
  0.274700;0.101090;,
  0.274700;0.094130;,
  0.259090;0.101090;,
  0.257370;0.094130;,
  0.295430;0.335370;,
  0.290780;0.316060;,
  0.290780;0.354690;,
  0.277660;0.371070;,
  0.257110;0.374000;,
  0.236560;0.371070;,
  0.223440;0.354690;,
  0.218790;0.335370;,
  0.303990;0.093170;,
  0.299710;0.100140;,
  0.290850;0.068350;,
  0.303530;0.068350;,
  0.292020;0.068050;,
  0.274700;0.068050;,
  0.257370;0.068050;,
  0.303990;0.067100;,
  0.291310;0.067100;,
  0.273980;0.067100;,
  0.256650;0.067100;,
  0.244760;0.067100;,
  0.255590;0.067220;,
  0.275580;0.067220;,
  0.295580;0.067220;,
  0.244300;0.068350;,
  0.256200;0.068350;,
  0.273520;0.068350;,
  0.290850;0.094430;,
  0.303530;0.094430;,
  0.299250;0.101390;,
  0.288720;0.101390;,
  0.277780;0.368660;,
  0.256820;0.373830;,
  0.256820;0.329180;,
  0.235860;0.368660;,
  0.223150;0.354520;,
  0.291310;0.041020;,
  0.273980;0.041020;,
  0.274800;0.034060;,
  0.289180;0.034060;,
  0.256650;0.041020;,
  0.260410;0.034060;,
  0.244760;0.041020;,
  0.250140;0.034060;,
  0.255590;0.093290;,
  0.275580;0.093290;,
  0.275580;0.100260;,
  0.259190;0.100260;,
  0.295580;0.093290;,
  0.291970;0.100260;,
  0.244300;0.094430;,
  0.256200;0.094430;,
  0.259960;0.101390;,
  0.249680;0.101390;,
  0.273520;0.094430;,
  0.274340;0.101390;,
  0.292020;0.041980;,
  0.274700;0.041980;,
  0.274700;0.035010;,
  0.290310;0.035010;,
  0.257370;0.041980;,
  0.259090;0.035010;,
  0.295140;0.335210;,
  0.290480;0.354520;,
  0.290480;0.315900;,
  0.278820;0.302090;,
  0.256820;0.296590;,
  0.234810;0.302090;,
  0.223150;0.315900;,
  0.218500;0.335210;,
  0.303990;0.041020;,
  0.299710;0.034060;;
 }
}
