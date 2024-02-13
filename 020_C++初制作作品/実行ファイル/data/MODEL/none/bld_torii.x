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
 266;
 -398.28174;842.90265;-57.57135;,
 -357.57263;842.90265;-40.70910;,
 -357.57263;96.20197;-40.70910;,
 -398.28174;96.20197;-57.57135;,
 -340.71039;842.90265;0.00000;,
 -340.71039;96.20197;0.00000;,
 -357.57263;842.90265;40.70910;,
 -357.57263;96.20197;40.70910;,
 -398.28174;842.90265;57.57135;,
 -398.28174;96.20197;57.57135;,
 -438.99124;842.90265;40.70910;,
 -438.99124;96.20197;40.70910;,
 -455.85379;842.90265;0.00000;,
 -455.85379;96.20197;0.00000;,
 -438.99124;842.90265;-40.70910;,
 -438.99124;96.20197;-40.70910;,
 -398.28174;842.90265;-57.57135;,
 -398.28174;96.20197;-57.57135;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;842.90265;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 -398.28174;96.20197;0.00000;,
 383.11942;842.90265;-57.57135;,
 423.82840;842.90265;-40.70910;,
 423.82840;96.20197;-40.70910;,
 383.11942;96.20197;-57.57135;,
 439.00076;843.19342;-0.72195;,
 439.00076;96.49283;-0.72195;,
 423.82840;842.90265;40.70910;,
 423.82840;96.20197;40.70910;,
 383.11942;842.90265;57.57135;,
 383.11942;96.20197;57.57135;,
 342.41061;842.90265;40.70910;,
 342.41061;96.20197;40.70910;,
 325.54852;842.90265;0.00000;,
 325.54852;96.20197;0.00000;,
 342.41061;842.90265;-40.70910;,
 342.41061;96.20197;-40.70910;,
 383.11942;842.90265;-57.57135;,
 383.11942;96.20197;-57.57135;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;842.90265;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 383.11942;96.20197;0.00000;,
 -546.06909;686.54645;-30.55740;,
 523.39185;686.54645;-30.55740;,
 523.39185;625.12628;-30.55740;,
 -546.06909;625.12628;-30.55740;,
 523.39185;686.54645;-30.55740;,
 523.39185;686.54645;30.55740;,
 523.39185;625.12628;30.55740;,
 523.39185;625.12628;-30.55740;,
 523.39185;686.54645;30.55740;,
 -546.06909;686.54645;30.55740;,
 -546.06909;625.12628;30.55740;,
 523.39185;625.12628;30.55740;,
 -546.06909;686.54645;30.55740;,
 -546.06909;686.54645;-30.55740;,
 -546.06909;625.12628;-30.55740;,
 -546.06909;625.12628;30.55740;,
 523.39185;686.54645;-30.55740;,
 -546.06909;686.54645;-30.55740;,
 -546.06909;625.12628;-30.55740;,
 523.39185;625.12628;-30.55740;,
 682.96252;914.19873;-74.61750;,
 682.96252;914.19873;74.61750;,
 682.96252;848.66412;74.61750;,
 682.96252;848.66412;-74.61750;,
 -705.63989;914.20935;74.61750;,
 -705.63989;914.20935;-74.61750;,
 -705.63989;848.67450;-74.61750;,
 -705.63989;848.67450;74.61750;,
 -633.24854;907.55908;-74.61750;,
 -633.07593;842.02411;-74.61750;,
 -705.63989;848.67450;-74.61750;,
 -705.63989;914.20935;-74.61750;,
 -651.12427;907.55908;74.61750;,
 -705.63989;914.20935;74.61750;,
 -705.63989;848.67450;74.61750;,
 -650.95190;842.02411;74.61750;,
 -651.12427;907.55908;74.61750;,
 -633.24854;907.55908;-74.61750;,
 -705.63989;914.20935;-74.61750;,
 -633.07593;842.02411;-74.61750;,
 -650.95190;842.02411;74.61750;,
 -705.63989;848.67450;-74.61750;,
 608.36365;907.55908;-74.61750;,
 682.96252;914.19873;-74.61750;,
 682.96252;848.66412;-74.61750;,
 608.20081;842.02411;-74.61750;,
 624.07336;842.02411;74.61750;,
 682.96252;848.66412;74.61750;,
 682.96252;914.19873;74.61750;,
 624.23633;907.55908;74.61750;,
 624.23633;907.55908;74.61750;,
 682.96252;914.19873;-74.61750;,
 608.36365;907.55908;-74.61750;,
 608.20081;842.02411;-74.61750;,
 682.96252;848.66412;-74.61750;,
 624.07336;842.02411;74.61750;,
 710.32776;973.53625;-74.61750;,
 710.32776;973.53625;74.61750;,
 710.32776;914.22278;74.61750;,
 710.32776;914.22278;-74.61750;,
 -733.00574;973.54675;74.61750;,
 -733.00574;973.54675;-74.61750;,
 -733.00574;914.23328;-74.61750;,
 -733.00574;914.23328;74.61750;,
 -633.40405;966.89661;-74.61750;,
 -633.24805;907.58301;-74.61750;,
 -733.00574;914.23328;-74.61750;,
 -733.00574;973.54675;-74.61750;,
 -651.28064;966.89661;74.61750;,
 -733.00574;973.54675;74.61750;,
 -733.00574;914.23328;74.61750;,
 -651.12427;907.58301;74.61750;,
 -651.28064;966.89661;74.61750;,
 -633.40405;966.89661;-74.61750;,
 -733.00574;973.54675;-74.61750;,
 -633.24805;907.58301;-74.61750;,
 -651.12427;907.58301;74.61750;,
 -733.00574;914.23328;-74.61750;,
 608.51111;966.89661;-74.61750;,
 710.32776;973.53625;-74.61750;,
 710.32776;914.22278;-74.61750;,
 608.36316;907.58301;-74.61750;,
 624.23633;907.58301;74.61750;,
 710.32776;914.22278;74.61750;,
 710.32776;973.53625;74.61750;,
 624.38403;966.89661;74.61750;,
 624.38403;966.89661;74.61750;,
 710.32776;973.53625;-74.61750;,
 608.51111;966.89661;-74.61750;,
 608.36316;907.58301;-74.61750;,
 710.32776;914.22278;-74.61750;,
 624.23633;907.58301;74.61750;,
 -40.68532;841.40399;-16.79535;,
 52.23173;841.40399;-16.79535;,
 52.23173;682.96442;-16.79535;,
 -40.68532;682.96442;-16.79535;,
 52.23173;841.40399;-16.79535;,
 52.23173;841.40399;16.79535;,
 52.23173;682.96442;16.79535;,
 52.23173;682.96442;-16.79535;,
 52.23173;841.40399;16.79535;,
 -40.68532;841.40399;16.79535;,
 -40.68532;682.96442;16.79535;,
 52.23173;682.96442;16.79535;,
 -40.68532;841.40399;16.79535;,
 -40.68532;841.40399;-16.79535;,
 -40.68532;682.96442;-16.79535;,
 -40.68532;682.96442;16.79535;,
 52.23173;841.40399;-16.79535;,
 -40.68532;841.40399;-16.79535;,
 -40.68532;682.96442;-16.79535;,
 52.23173;682.96442;-16.79535;,
 -398.41507;133.56744;-81.22050;,
 -340.98367;133.56744;-57.43155;,
 -340.98367;75.41885;-57.43155;,
 -398.41507;75.41885;-81.22050;,
 -317.19458;133.56744;0.00000;,
 -317.19458;75.41885;0.00000;,
 -340.98367;133.56744;57.43155;,
 -340.98367;75.41885;57.43155;,
 -398.41507;133.56744;81.22050;,
 -398.41507;75.41885;81.22050;,
 -455.84662;133.56744;57.43155;,
 -455.84662;75.41885;57.43155;,
 -479.63620;133.56744;0.00000;,
 -479.63620;75.41885;0.00000;,
 -455.84662;133.56744;-57.43155;,
 -455.84662;75.41885;-57.43155;,
 -398.41507;133.56744;-81.22050;,
 -398.41507;75.41885;-81.22050;,
 -340.98367;17.27032;-57.43155;,
 -398.41507;17.27032;-81.22050;,
 -317.19458;17.27032;0.00000;,
 -340.98367;17.27032;57.43155;,
 -398.41507;17.27032;81.22050;,
 -455.84662;17.27032;57.43155;,
 -479.63620;17.27032;0.00000;,
 -455.84662;17.27032;-57.43155;,
 -398.41507;17.27032;-81.22050;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;133.56744;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 -398.41507;17.27032;0.00000;,
 383.21201;133.56744;-81.22050;,
 440.64325;133.56744;-57.43155;,
 440.64325;75.41885;-57.43155;,
 383.21201;75.41885;-81.22050;,
 464.43250;133.56744;0.00000;,
 464.43250;75.41885;0.00000;,
 440.64325;133.56744;57.43155;,
 440.64325;75.41885;57.43155;,
 383.21201;133.56744;81.22050;,
 383.21201;75.41885;81.22050;,
 325.78043;133.56744;57.43155;,
 325.78043;75.41885;57.43155;,
 301.99161;133.56744;0.00000;,
 301.99161;75.41885;0.00000;,
 325.78043;133.56744;-57.43155;,
 325.78043;75.41885;-57.43155;,
 383.21201;133.56744;-81.22050;,
 383.21201;75.41885;-81.22050;,
 440.64325;17.27032;-57.43155;,
 383.21201;17.27032;-81.22050;,
 464.43250;17.27032;0.00000;,
 440.64325;17.27032;57.43155;,
 383.21201;17.27032;81.22050;,
 325.78043;17.27032;57.43155;,
 301.99161;17.27032;0.00000;,
 325.78043;17.27032;-57.43155;,
 383.21201;17.27032;-81.22050;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;133.56744;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;,
 383.21201;17.27032;0.00000;;
 
 152;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;80,73,84,85;,
 4;86,87,74,83;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,92;,
 4;107,108,95,109;,
 4;110,111,112,113;,
 4;110,113,97,96;,
 4;114,115,116,117;,
 4;114,117,100,103;,
 4;118,89,119,120;,
 4;118,120,105,104;,
 4;121,122,90,123;,
 4;121,123,108,107;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,128;,
 4;143,144,131,145;,
 4;146,147,148,149;,
 4;146,149,133,132;,
 4;150,151,152,153;,
 4;150,153,136,139;,
 4;154,125,155,156;,
 4;154,156,141,140;,
 4;157,158,126,159;,
 4;157,159,144,143;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;181,184,185,182;,
 4;184,186,187,185;,
 4;186,188,189,187;,
 4;188,190,191,189;,
 4;190,192,193,191;,
 4;192,194,195,193;,
 4;194,196,197,195;,
 4;183,182,198,199;,
 4;182,185,200,198;,
 4;185,187,201,200;,
 4;187,189,202,201;,
 4;189,191,203,202;,
 4;191,193,204,203;,
 4;193,195,205,204;,
 4;195,197,206,205;,
 3;207,181,180;,
 3;208,184,181;,
 3;209,186,184;,
 3;210,188,186;,
 3;211,190,188;,
 3;212,192,190;,
 3;213,194,192;,
 3;214,196,194;,
 3;215,199,198;,
 3;216,198,200;,
 3;217,200,201;,
 3;218,201,202;,
 3;219,202,203;,
 3;220,203,204;,
 3;221,204,205;,
 3;222,205,206;,
 4;223,224,225,226;,
 4;224,227,228,225;,
 4;227,229,230,228;,
 4;229,231,232,230;,
 4;231,233,234,232;,
 4;233,235,236,234;,
 4;235,237,238,236;,
 4;237,239,240,238;,
 4;226,225,241,242;,
 4;225,228,243,241;,
 4;228,230,244,243;,
 4;230,232,245,244;,
 4;232,234,246,245;,
 4;234,236,247,246;,
 4;236,238,248,247;,
 4;238,240,249,248;,
 3;250,224,223;,
 3;251,227,224;,
 3;252,229,227;,
 3;253,231,229;,
 3;254,233,231;,
 3;255,235,233;,
 3;256,237,235;,
 3;257,239,237;,
 3;258,242,241;,
 3;259,241,243;,
 3;260,243,244;,
 3;261,244,245;,
 3;262,245,246;,
 3;263,246,247;,
 3;264,247,248;,
 3;265,248,249;;
 
 MeshMaterialList {
  3;
  152;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.000000;0.132000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.524000;0.524000;0.524000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  87;
  0.000000;1.000000;0.000000;,
  0.000002;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000002;0.000000;1.000000;,
  -0.707103;0.000000;0.707110;,
  -1.000000;0.000000;0.000000;,
  -0.707103;0.000000;-0.707110;,
  0.000000;-1.000000;-0.000000;,
  -0.001301;0.999999;-0.000017;,
  -0.000001;0.000000;-1.000000;,
  0.717651;0.000000;-0.696403;,
  0.999983;0.000000;-0.005805;,
  0.721681;0.000000;0.692226;,
  -0.000001;0.000000;1.000000;,
  -0.707109;0.000000;0.707105;,
  -0.707109;0.000000;-0.707105;,
  0.001301;-0.999999;0.000017;,
  -0.002636;0.999993;-0.002636;,
  -0.005204;0.999986;-0.000067;,
  -0.002568;0.999993;0.002568;,
  0.002637;-0.999993;0.002637;,
  0.005206;-0.999986;0.000067;,
  0.002569;-0.999993;-0.002569;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.053224;0.998579;0.002744;,
  0.106296;0.994319;0.005479;,
  -0.053076;-0.998587;-0.002737;,
  -0.106002;-0.994351;-0.005466;,
  -0.050317;0.998731;0.002360;,
  -0.100506;0.994925;0.004715;,
  0.050194;-0.998737;-0.002355;,
  0.100262;-0.994950;-0.004705;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.036957;0.999315;0.001996;,
  0.073863;0.997260;0.003990;,
  -0.036893;-0.999317;-0.001993;,
  -0.073736;-0.997270;-0.003984;,
  -0.035548;0.999366;0.001731;,
  -0.071051;0.997467;0.003461;,
  0.035492;-0.999368;-0.001729;,
  0.070939;-0.997475;-0.003456;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707106;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707106;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707103;0.000000;0.707110;,
  -1.000000;0.000000;0.000000;,
  -0.707103;0.000000;-0.707110;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.707103;0.000000;0.707110;,
  -0.707103;0.000000;-0.707110;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000001;0.000000;-1.000000;,
  0.707106;0.000000;-0.707108;,
  1.000000;0.000000;0.000000;,
  0.707106;0.000000;0.707108;,
  0.000001;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707106;,
  -0.707107;0.000000;-0.707106;,
  0.000001;0.000000;-1.000000;,
  0.000001;0.000000;1.000000;,
  -0.707107;0.000000;0.707106;,
  0.000000;-1.000000;-0.000000;;
  152;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,7,7,16;,
  4;7,17,17,7;,
  4;17,11,11,17;,
  3;10,19,0;,
  3;10,20,19;,
  3;10,21,20;,
  3;10,0,21;,
  3;10,0,0;,
  3;10,0,0;,
  3;10,0,0;,
  3;10,0,0;,
  3;18,9,22;,
  3;18,22,23;,
  3;18,23,24;,
  3;18,24,9;,
  3;18,9,9;,
  3;18,9,9;,
  3;18,9,9;,
  3;18,9,9;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;32,32,32,32;,
  4;31,31,31,31;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,36,36;,
  4;37,37,38,38;,
  4;33,33,33,33;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;34,34,34,34;,
  4;39,40,40,39;,
  4;39,39,35,35;,
  4;41,42,42,41;,
  4;41,41,37,37;,
  4;44,44,44,44;,
  4;43,43,43,43;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,48,48;,
  4;49,49,50,50;,
  4;45,45,45,45;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;46,46,46,46;,
  4;51,52,52,51;,
  4;51,51,47,47;,
  4;53,54,54,53;,
  4;53,53,49,49;,
  4;45,45,45,45;,
  4;44,44,44,44;,
  4;46,46,46,46;,
  4;43,43,43,43;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;58,59,59,66;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,67,61;,
  4;62,63,63,67;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,58,66,65;,
  4;66,59,59,68;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,67,69,61;,
  4;67,63,70,69;,
  4;63,64,64,70;,
  4;64,65,71,64;,
  4;65,66,68,71;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  3;72,72,72;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,82,80;,
  4;81,74,74,82;,
  4;74,75,75,83;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,84,77;,
  4;78,79,85,84;,
  4;79,80,80,85;,
  4;80,82,82,80;,
  4;82,74,83,82;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  3;86,86,86;,
  3;86,86,86;,
  3;86,86,86;,
  3;86,86,86;,
  3;86,86,86;,
  3;86,86,86;,
  3;86,86,86;,
  3;86,86,86;;
 }
 MeshTextureCoords {
  266;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.067640;0.000000;,
  0.067800;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.949060;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.948900;1.000000;,
  0.050940;0.000000;,
  0.067640;1.000000;,
  0.000000;1.000000;,
  0.067800;0.000000;,
  0.051100;1.000000;,
  0.000000;0.000000;,
  0.930290;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.930140;1.000000;,
  0.055030;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.054870;0.000000;,
  0.945130;0.000000;,
  1.000000;1.000000;,
  0.930290;1.000000;,
  0.930140;0.000000;,
  1.000000;0.000000;,
  0.944970;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.088540;0.000000;,
  0.088680;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.927350;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.927210;1.000000;,
  0.072650;0.000000;,
  0.088540;1.000000;,
  0.000000;1.000000;,
  0.088680;0.000000;,
  0.072790;1.000000;,
  0.000000;0.000000;,
  0.909490;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.909360;1.000000;,
  0.076530;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.076400;0.000000;,
  0.923600;0.000000;,
  1.000000;1.000000;,
  0.909490;1.000000;,
  0.909360;0.000000;,
  1.000000;0.000000;,
  0.923470;1.000000;,
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
  0.125000;0.000000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.625000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  0.875000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.375000;0.000000;,
  0.375000;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.625000;0.500000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  0.875000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
