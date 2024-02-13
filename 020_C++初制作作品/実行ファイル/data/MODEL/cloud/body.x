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
 82;
 7.58994;-4.59947;-2.29807;,
 3.86833;-5.69715;-4.01094;,
 3.63681;-1.76862;-3.97053;,
 6.62219;-1.76862;-2.29807;,
 0.00000;-6.38951;-4.11247;,
 0.00000;-1.76862;-4.01644;,
 -3.86834;-5.69715;-4.01094;,
 -3.63683;-1.76862;-3.97053;,
 -7.58995;-4.59947;-2.29807;,
 -6.62220;-1.76862;-2.29807;,
 2.51722;0.88575;-4.36347;,
 5.00646;0.88575;-2.29807;,
 0.00000;0.88575;-4.55000;,
 -2.51723;0.88575;-4.36347;,
 -5.00647;0.88575;-2.29807;,
 5.89384;5.31825;-5.94856;,
 9.74388;5.31825;-2.29807;,
 0.00000;5.31825;-6.13509;,
 -5.89385;5.31825;-5.94856;,
 -9.74388;5.31825;-2.29807;,
 5.65657;11.23477;-4.51214;,
 8.41534;11.23477;-2.29807;,
 0.00000;11.23477;-4.69867;,
 -5.65658;11.23477;-4.51214;,
 -8.41535;11.23477;-2.29807;,
 3.81950;11.23477;0.23053;,
 8.41534;11.23477;0.23053;,
 0.00000;11.23477;0.23053;,
 -3.81950;11.23477;0.23053;,
 -8.41535;11.23477;0.23053;,
 8.41534;11.23477;0.23053;,
 3.81950;11.23477;0.23053;,
 5.58731;11.03192;4.54518;,
 8.34187;11.23477;3.10590;,
 0.00000;11.23477;0.23053;,
 0.00000;10.84540;4.45378;,
 -3.81950;11.23477;0.23053;,
 -5.58733;11.03192;4.54518;,
 -8.41535;11.23477;0.23053;,
 -8.34188;11.23477;3.10589;,
 5.48263;5.31825;5.61160;,
 9.74388;5.31825;2.99568;,
 0.00000;5.31825;5.52386;,
 -5.48264;5.31825;5.61160;,
 -9.74388;5.31825;2.99568;,
 1.88731;1.03206;4.01504;,
 5.00646;0.88575;3.10590;,
 0.00000;1.03206;4.01504;,
 -1.88732;1.03206;4.01504;,
 -5.00647;0.88575;3.10589;,
 2.59354;-1.76862;3.90819;,
 6.62219;-1.76862;3.10590;,
 0.00000;-1.76862;3.90820;,
 -2.59356;-1.76862;3.90819;,
 -6.62220;-1.76862;3.10589;,
 3.81950;-5.69715;3.75337;,
 7.58994;-4.73701;3.10590;,
 0.00000;-6.38951;3.80176;,
 -3.81950;-5.69715;3.75337;,
 -7.58995;-4.73701;3.10589;,
 3.81950;-5.69715;0.23053;,
 7.97291;-4.73701;0.23053;,
 0.00000;-6.38951;0.23053;,
 -3.81950;-5.69715;0.23053;,
 -7.97291;-4.73701;0.23053;,
 7.97291;-4.73701;0.23053;,
 3.81950;-5.69715;0.23053;,
 0.00000;-6.38951;0.23053;,
 -3.81950;-5.69715;0.23053;,
 -7.97291;-4.73701;0.23053;,
 -7.00516;-1.76862;0.23053;,
 -7.00516;-1.76862;0.23053;,
 -5.00647;0.88575;0.23053;,
 -5.00647;0.88575;0.23053;,
 -9.74388;5.31825;0.23053;,
 -9.74388;5.31825;0.23053;,
 7.00515;-1.76862;0.23053;,
 7.00515;-1.76862;0.23053;,
 5.00646;0.88575;0.23053;,
 5.00646;0.88575;0.23053;,
 9.74388;5.31825;0.23053;,
 9.74388;5.31825;0.23053;;
 
 64;
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
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;33,32,40,41;,
 4;32,35,42,40;,
 4;35,37,43,42;,
 4;37,39,44,43;,
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
 4;65,66,1,0;,
 4;66,67,4,1;,
 4;67,68,6,4;,
 4;68,69,8,6;,
 4;64,59,54,70;,
 4;8,69,71,9;,
 4;70,54,49,72;,
 4;9,71,73,14;,
 4;72,49,44,74;,
 4;14,73,75,19;,
 4;74,44,39,38;,
 4;19,75,29,24;,
 4;56,61,76,51;,
 4;65,0,3,77;,
 4;51,76,78,46;,
 4;77,3,11,79;,
 4;46,78,80,41;,
 4;79,11,16,81;,
 4;41,80,30,33;,
 4;81,16,21,26;;
 
 MeshMaterialList {
  3;
  64;
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
    "data\\TEXTURE\\cloudUV.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\cloudUV.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\cloudUV.png";
   }
  }
 }
 MeshNormals {
  98;
  0.780096;0.225738;-0.583517;,
  0.232712;0.051430;-0.971185;,
  0.000000;0.015903;-0.999874;,
  -0.232712;0.051430;-0.971185;,
  -0.780097;0.225737;-0.583516;,
  0.777303;0.332635;-0.533998;,
  0.273884;0.039667;-0.960944;,
  0.000000;-0.076949;-0.997035;,
  -0.273884;0.039667;-0.960944;,
  -0.777303;0.332635;-0.533998;,
  0.703161;-0.441097;-0.557672;,
  0.323492;-0.245796;-0.913749;,
  0.000000;-0.259035;-0.965868;,
  -0.323492;-0.245796;-0.913749;,
  -0.703162;-0.441096;-0.557672;,
  0.867062;-0.283958;-0.409354;,
  0.357427;-0.149843;-0.921842;,
  -0.000000;-0.057488;-0.998346;,
  -0.357427;-0.149849;-0.921841;,
  -0.867062;-0.283958;-0.409354;,
  0.887572;0.219090;-0.405235;,
  0.359170;0.221287;-0.906658;,
  -0.000000;0.236522;-0.971626;,
  -0.359171;0.221274;-0.906661;,
  -0.887573;0.219089;-0.405234;,
  -0.010086;0.999823;0.015863;,
  -0.009335;0.999591;0.027045;,
  -0.000000;0.999269;0.038231;,
  0.009335;0.999591;0.027045;,
  0.010086;0.999823;0.015863;,
  -0.020168;0.999293;0.031721;,
  -0.018666;0.998363;0.054074;,
  -0.000000;0.997076;0.076411;,
  0.018666;0.998363;0.054074;,
  0.020168;0.999293;0.031721;,
  0.437307;-0.188923;0.879244;,
  0.215988;-0.136261;0.966841;,
  -0.000000;-0.076705;0.997054;,
  -0.215989;-0.136261;0.966841;,
  -0.437310;-0.188924;0.879243;,
  0.304895;-0.216731;0.927398;,
  0.149665;-0.205032;0.967245;,
  -0.000000;-0.188725;0.982030;,
  -0.149666;-0.205032;0.967244;,
  -0.304897;-0.216731;0.927397;,
  0.207081;0.056527;0.976689;,
  0.106511;0.011720;0.994242;,
  -0.000000;-0.033203;0.999449;,
  -0.106512;0.011720;0.994242;,
  -0.207084;0.056528;0.976689;,
  0.175883;0.036652;0.983729;,
  0.093002;0.004202;0.995657;,
  -0.000000;-0.028283;0.999600;,
  -0.093003;0.004202;0.995657;,
  -0.175885;0.036653;0.983728;,
  0.244763;-0.969490;-0.013423;,
  0.211412;-0.977376;-0.006457;,
  0.000000;-1.000000;0.000522;,
  -0.211412;-0.977376;-0.006457;,
  -0.244763;-0.969490;-0.013423;,
  -0.897017;0.441979;-0.003950;,
  -0.827615;0.561285;-0.003605;,
  -0.683217;-0.730215;0.000000;,
  0.897017;0.441979;-0.003951;,
  0.827615;0.561285;-0.003606;,
  0.683216;-0.730216;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.838889;0.204961;0.504238;,
  0.241211;0.165104;0.956325;,
  -0.000000;0.186973;0.982365;,
  -0.241212;0.165104;0.956325;,
  -0.838890;0.204960;0.504237;,
  0.235992;-0.971639;0.014995;,
  0.207273;-0.978254;0.007501;,
  0.000000;-1.000000;-0.000000;,
  -0.207273;-0.978254;0.007501;,
  -0.235992;-0.971639;0.014995;,
  0.215508;-0.976288;-0.020422;,
  0.253317;-0.966479;-0.041830;,
  0.000000;-1.000000;0.001043;,
  -0.215508;-0.976288;-0.020421;,
  -0.253316;-0.966479;-0.041829;,
  -0.949632;0.313339;-0.004222;,
  -0.943217;0.307506;0.125624;,
  -0.894147;0.438580;0.090272;,
  -0.826444;0.560515;0.053039;,
  -0.826128;0.560253;-0.060238;,
  -0.683217;-0.730215;0.000000;,
  -0.975061;0.221851;0.006215;,
  -0.974372;0.224600;0.012430;,
  0.943217;0.307508;0.125625;,
  0.949632;0.313340;-0.004222;,
  0.894146;0.438581;0.090272;,
  0.826444;0.560515;0.053038;,
  0.826128;0.560253;-0.060238;,
  0.683216;-0.730216;-0.000000;,
  0.974371;0.224602;0.012430;,
  0.975061;0.221852;0.006215;;
  64;
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
  4;16,17,22,21;,
  4;17,18,23,22;,
  4;18,19,24,23;,
  4;66,66,26,25;,
  4;66,66,27,26;,
  4;66,66,28,27;,
  4;66,66,29,28;,
  4;25,26,31,30;,
  4;26,27,32,31;,
  4;27,28,33,32;,
  4;28,29,34,33;,
  4;67,68,36,35;,
  4;68,69,37,36;,
  4;69,70,38,37;,
  4;70,71,39,38;,
  4;35,36,41,40;,
  4;36,37,42,41;,
  4;37,38,43,42;,
  4;38,39,44,43;,
  4;40,41,46,45;,
  4;41,42,47,46;,
  4;42,43,48,47;,
  4;43,44,49,48;,
  4;45,46,51,50;,
  4;46,47,52,51;,
  4;47,48,53,52;,
  4;48,49,54,53;,
  4;72,73,56,55;,
  4;73,74,57,56;,
  4;74,75,58,57;,
  4;75,76,59,58;,
  4;55,56,77,78;,
  4;56,57,79,77;,
  4;57,58,80,79;,
  4;58,59,81,80;,
  4;82,83,84,60;,
  4;4,82,60,9;,
  4;60,84,85,61;,
  4;9,60,61,86;,
  4;62,87,87,62;,
  4;14,62,62,19;,
  4;88,89,71,88;,
  4;19,88,88,24;,
  4;90,91,63,92;,
  4;91,0,5,63;,
  4;92,63,64,93;,
  4;63,5,94,64;,
  4;95,65,65,95;,
  4;65,10,15,65;,
  4;96,97,97,67;,
  4;97,15,20,97;;
 }
 MeshTextureCoords {
  82;
  0.592288;0.953436;,
  0.666621;0.977679;,
  0.671246;0.890916;,
  0.611617;0.890916;,
  0.743886;0.992970;,
  0.743886;0.890916;,
  0.821150;0.977679;,
  0.816526;0.890916;,
  0.895483;0.953436;,
  0.876154;0.890916;,
  0.693608;0.832293;,
  0.643889;0.832293;,
  0.743886;0.832293;,
  0.794163;0.832293;,
  0.843882;0.832293;,
  0.626165;0.734400;,
  0.549267;0.734400;,
  0.743886;0.734400;,
  0.861606;0.734400;,
  0.938505;0.734400;,
  0.630904;0.603732;,
  0.575802;0.603732;,
  0.743886;0.603732;,
  0.856867;0.603732;,
  0.911969;0.603732;,
  0.667597;0.603732;,
  0.575802;0.603732;,
  0.743886;0.603732;,
  0.820174;0.603732;,
  0.911969;0.603732;,
  0.079500;0.644203;,
  0.160792;0.644203;,
  0.129523;0.648170;,
  0.080800;0.644203;,
  0.228351;0.644203;,
  0.228351;0.651818;,
  0.295911;0.644203;,
  0.327180;0.648170;,
  0.377203;0.644203;,
  0.375903;0.644203;,
  0.131374;0.759920;,
  0.056001;0.759920;,
  0.228351;0.759920;,
  0.325328;0.759920;,
  0.400702;0.759920;,
  0.194968;0.843750;,
  0.139797;0.846612;,
  0.228351;0.843750;,
  0.261734;0.843750;,
  0.316906;0.846612;,
  0.182476;0.898527;,
  0.111218;0.898527;,
  0.228351;0.898527;,
  0.274226;0.898527;,
  0.345485;0.898527;,
  0.160792;0.975362;,
  0.094100;0.956583;,
  0.228351;0.988903;,
  0.295911;0.975362;,
  0.362603;0.956583;,
  0.160792;0.975362;,
  0.087326;0.956583;,
  0.228351;0.988903;,
  0.295911;0.975362;,
  0.369377;0.956583;,
  0.584639;0.956474;,
  0.667597;0.977679;,
  0.743886;0.992970;,
  0.820174;0.977679;,
  0.903132;0.956474;,
  0.352259;0.898527;,
  0.883803;0.890916;,
  0.316906;0.846612;,
  0.843882;0.832293;,
  0.400702;0.759920;,
  0.938505;0.734400;,
  0.104444;0.898527;,
  0.603969;0.890916;,
  0.139797;0.846612;,
  0.643889;0.832293;,
  0.056001;0.759920;,
  0.549267;0.734400;;
 }
}
