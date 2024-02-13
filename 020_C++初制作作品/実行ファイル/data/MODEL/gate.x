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
 204;
 -95.25586;261.69458;-98.41848;,
 -65.00000;261.69458;-119.48267;,
 -65.00000;196.69461;-130.00000;,
 -130.00000;196.69461;-130.00000;,
 0.00000;261.69458;-130.00000;,
 0.00000;196.69461;-130.00000;,
 65.00000;261.69458;-119.48267;,
 65.00000;196.69461;-130.00000;,
 95.25586;261.69458;-98.41848;,
 130.00000;196.69461;-130.00000;,
 -65.00000;131.69463;-130.00000;,
 -130.00000;131.69463;-130.00000;,
 130.00000;131.69463;-130.00000;,
 65.00000;131.69463;-130.00000;,
 -65.00000;66.69462;-130.00000;,
 -130.00000;66.69462;-130.00000;,
 130.00000;66.69462;-130.00000;,
 65.00000;66.69462;-130.00000;,
 -65.00000;1.69463;-130.00000;,
 -130.00000;1.69463;-130.00000;,
 130.00000;1.69463;-130.00000;,
 65.00000;1.69463;-130.00000;,
 95.25586;261.69458;-98.41848;,
 113.73672;261.69458;-65.00000;,
 130.00000;196.69461;-65.00000;,
 130.00000;196.69461;-130.00000;,
 130.00000;261.69458;0.00000;,
 130.00000;196.69461;0.00000;,
 116.85383;261.69458;65.00000;,
 130.00000;196.69461;65.00000;,
 89.72235;261.69458;88.53233;,
 130.00000;196.69461;130.00000;,
 130.00000;131.69463;-65.00000;,
 130.00000;131.69463;-130.00000;,
 130.00000;131.69463;130.00000;,
 130.00000;131.69463;65.00000;,
 130.00000;66.69462;-65.00000;,
 130.00000;66.69462;-130.00000;,
 130.00000;66.69462;130.00000;,
 130.00000;66.69462;65.00000;,
 130.00000;1.69463;-65.00000;,
 130.00000;1.69463;-130.00000;,
 130.00000;1.69463;130.00000;,
 130.00000;1.69463;65.00000;,
 89.72235;261.69458;88.53233;,
 65.00000;261.69458;116.53965;,
 65.00000;196.69461;130.00000;,
 130.00000;196.69461;130.00000;,
 0.00000;261.69458;130.00000;,
 0.00000;196.69461;130.00000;,
 -65.00000;261.69458;116.53965;,
 -65.00000;196.69461;130.00000;,
 -89.72235;261.69458;88.53233;,
 -130.00000;196.69461;130.00000;,
 65.00000;131.69463;130.00000;,
 130.00000;131.69463;130.00000;,
 -130.00000;131.69463;130.00000;,
 -65.00000;131.69463;130.00000;,
 65.00000;66.69462;130.00000;,
 130.00000;66.69462;130.00000;,
 -130.00000;66.69462;130.00000;,
 -65.00000;66.69462;130.00000;,
 65.00000;1.69463;130.00000;,
 130.00000;1.69463;130.00000;,
 -130.00000;1.69463;130.00000;,
 -65.00000;1.69463;130.00000;,
 -89.72235;261.69458;88.53233;,
 -116.85383;261.69458;65.00000;,
 -130.00000;196.69461;65.00000;,
 -130.00000;196.69461;130.00000;,
 -130.00000;261.69458;0.00000;,
 -130.00000;196.69461;0.00000;,
 -113.73672;261.69458;-65.00000;,
 -130.00000;196.69461;-65.00000;,
 -95.25586;261.69458;-98.41848;,
 -130.00000;196.69461;-130.00000;,
 -130.00000;131.69463;65.00000;,
 -130.00000;131.69463;130.00000;,
 -130.00000;131.69463;-130.00000;,
 -130.00000;131.69463;-65.00000;,
 -130.00000;66.69462;65.00000;,
 -130.00000;66.69462;130.00000;,
 -130.00000;66.69462;-130.00000;,
 -130.00000;66.69462;-65.00000;,
 -130.00000;1.69463;65.00000;,
 -130.00000;1.69463;130.00000;,
 -130.00000;1.69463;-130.00000;,
 -130.00000;1.69463;-65.00000;,
 -65.00000;261.69458;116.53965;,
 -65.00000;302.92902;65.00000;,
 -116.85383;261.69458;65.00000;,
 0.00000;302.92902;65.00000;,
 65.00000;261.69458;116.53965;,
 65.00000;302.92902;65.00000;,
 116.85383;261.69458;65.00000;,
 -65.00000;302.92902;0.00000;,
 -130.00000;261.69458;0.00000;,
 0.00000;302.92902;0.00000;,
 65.00000;302.92902;0.00000;,
 130.00000;261.69458;0.00000;,
 -65.00000;302.92902;-65.00000;,
 -113.73672;261.69458;-65.00000;,
 0.00000;302.92902;-65.00000;,
 65.00000;302.92902;-65.00000;,
 113.73672;261.69458;-65.00000;,
 -65.00000;261.69458;-119.48267;,
 -95.25586;261.69458;-98.41848;,
 0.00000;261.69458;-130.00000;,
 65.00000;261.69458;-119.48267;,
 95.25586;261.69458;-98.41848;,
 -130.00000;1.69463;65.00000;,
 -65.00000;1.69463;65.00000;,
 -65.00000;1.69463;130.00000;,
 0.00000;1.69463;65.00000;,
 0.00000;1.69463;130.00000;,
 65.00000;1.69463;65.00000;,
 65.00000;1.69463;130.00000;,
 130.00000;1.69463;65.00000;,
 -130.00000;1.69463;0.00000;,
 -65.00000;1.69463;0.00000;,
 0.00000;1.69463;0.00000;,
 65.00000;1.69463;0.00000;,
 130.00000;1.69463;0.00000;,
 -130.00000;1.69463;-65.00000;,
 -65.00000;1.69463;-65.00000;,
 0.00000;1.69463;-65.00000;,
 65.00000;1.69463;-65.00000;,
 130.00000;1.69463;-65.00000;,
 -130.00000;1.69463;-130.00000;,
 -65.00000;1.69463;-130.00000;,
 0.00000;1.69463;-130.00000;,
 65.00000;1.69463;-130.00000;,
 130.00000;1.69463;-130.00000;,
 0.00000;196.69461;-60.70464;,
 -65.00000;196.69461;-60.70464;,
 -65.00000;131.69463;-60.70464;,
 0.00000;131.69463;-60.70464;,
 65.00000;196.69461;-60.70464;,
 65.00000;131.69463;-60.70464;,
 -65.00000;66.69462;-60.70464;,
 0.00000;66.69462;-60.70464;,
 65.00000;66.69462;-60.70464;,
 -65.00000;1.69463;-60.70464;,
 0.00000;1.69463;-60.70464;,
 0.00000;1.69463;-130.00000;,
 65.00000;1.69463;-60.70464;,
 0.00000;196.69461;60.70464;,
 65.00000;196.69461;60.70464;,
 65.00000;131.69463;60.70464;,
 0.00000;131.69463;60.70464;,
 -65.00000;196.69461;60.70464;,
 -65.00000;131.69463;60.70464;,
 65.00000;66.69462;60.70464;,
 0.00000;66.69462;60.70464;,
 -65.00000;66.69462;60.70464;,
 65.00000;1.69463;60.70464;,
 0.00000;1.69463;60.70464;,
 -65.00000;1.69463;60.70464;,
 93.52876;196.69461;0.00000;,
 93.52876;196.69461;-65.00000;,
 93.52876;131.69463;-65.00000;,
 93.52876;196.69461;65.00000;,
 93.52876;131.69463;65.00000;,
 93.52876;66.69462;-65.00000;,
 93.52876;66.69462;65.00000;,
 93.52876;1.69463;-65.00000;,
 93.52876;1.69463;0.00000;,
 130.00000;1.69463;0.00000;,
 93.52876;1.69463;65.00000;,
 -93.52876;196.69461;0.00000;,
 -93.52876;196.69461;65.00000;,
 -93.52876;131.69463;65.00000;,
 -93.52876;196.69461;-65.00000;,
 -93.52876;131.69463;-65.00000;,
 -93.52876;66.69462;65.00000;,
 -93.52876;66.69462;-65.00000;,
 -93.52876;1.69463;65.00000;,
 -93.52876;1.69463;0.00000;,
 -130.00000;1.69463;0.00000;,
 -93.52876;1.69463;-65.00000;,
 67.99890;196.69461;0.00000;,
 67.99890;196.69461;-65.00000;,
 67.99890;131.69463;-65.00000;,
 67.99890;131.69463;0.00000;,
 67.99890;196.69461;65.00000;,
 67.99890;131.69463;65.00000;,
 67.99890;66.69462;-65.00000;,
 67.99890;66.69462;0.00000;,
 67.99890;66.69462;65.00000;,
 67.99890;1.69463;-65.00000;,
 67.99890;1.69463;0.00000;,
 67.99890;1.69463;65.00000;,
 -67.99890;196.69461;0.00000;,
 -67.99890;196.69461;65.00000;,
 -67.99890;131.69463;65.00000;,
 -67.99890;131.69463;0.00000;,
 -67.99890;196.69461;-65.00000;,
 -67.99890;131.69463;-65.00000;,
 -67.99890;66.69462;65.00000;,
 -67.99890;66.69462;0.00000;,
 -67.99890;66.69462;-65.00000;,
 -67.99890;1.69463;65.00000;,
 -67.99890;1.69463;0.00000;,
 -67.99890;1.69463;-65.00000;;
 
 156;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;7,9,12,13;,
 4;11,10,14,15;,
 4;13,12,16,17;,
 4;15,14,18,19;,
 4;17,16,20,21;,
 4;22,23,24,25;,
 4;23,26,27,24;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;25,24,32,33;,
 4;29,31,34,35;,
 4;33,32,36,37;,
 4;35,34,38,39;,
 4;37,36,40,41;,
 4;39,38,42,43;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;47,46,54,55;,
 4;51,53,56,57;,
 4;55,54,58,59;,
 4;57,56,60,61;,
 4;59,58,62,63;,
 4;61,60,64,65;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;69,68,76,77;,
 4;73,75,78,79;,
 4;77,76,80,81;,
 4;79,78,82,83;,
 4;81,80,84,85;,
 4;83,82,86,87;,
 4;66,88,89,90;,
 4;88,48,91,89;,
 4;48,92,93,91;,
 4;92,30,94,93;,
 4;90,89,95,96;,
 4;89,91,97,95;,
 4;91,93,98,97;,
 4;93,94,99,98;,
 4;96,95,100,101;,
 4;95,97,102,100;,
 4;97,98,103,102;,
 4;98,99,104,103;,
 4;101,100,105,106;,
 4;100,102,107,105;,
 4;102,103,108,107;,
 4;103,104,109,108;,
 4;110,111,112,85;,
 4;111,113,114,112;,
 4;113,115,116,114;,
 4;115,117,42,116;,
 4;118,119,111,110;,
 4;119,120,113,111;,
 4;120,121,115,113;,
 4;121,122,117,115;,
 4;123,124,119,118;,
 4;124,125,120,119;,
 4;125,126,121,120;,
 4;126,127,122,121;,
 4;128,129,124,123;,
 4;129,130,125,124;,
 4;130,131,126,125;,
 4;131,132,127,126;,
 4;133,134,2,5;,
 4;134,135,10,2;,
 4;134,133,136,135;,
 4;137,133,5,7;,
 4;138,137,7,13;,
 4;133,137,138,136;,
 4;135,139,14,10;,
 4;135,136,140,139;,
 4;141,138,13,17;,
 4;136,138,141,140;,
 4;142,143,144,18;,
 4;139,142,18,14;,
 4;139,140,143,142;,
 4;145,141,17,21;,
 4;143,145,21,144;,
 4;140,141,145,143;,
 4;146,147,46,49;,
 4;147,148,54,46;,
 4;147,146,149,148;,
 4;150,146,49,51;,
 4;151,150,51,57;,
 4;146,150,151,149;,
 4;148,152,58,54;,
 4;148,149,153,152;,
 4;154,151,57,61;,
 4;149,151,154,153;,
 4;155,156,114,62;,
 4;152,155,62,58;,
 4;152,153,156,155;,
 4;157,154,61,65;,
 4;156,157,65,114;,
 4;153,154,157,156;,
 4;158,159,24,27;,
 4;159,160,32,24;,
 4;161,158,27,29;,
 4;162,161,29,35;,
 4;160,163,36,32;,
 4;164,162,35,39;,
 4;165,166,167,40;,
 4;163,165,40,36;,
 4;168,164,39,43;,
 4;166,168,43,167;,
 4;169,170,68,71;,
 4;170,171,76,68;,
 4;172,169,71,73;,
 4;173,172,73,79;,
 4;171,174,80,76;,
 4;175,173,79,83;,
 4;176,177,178,84;,
 4;174,176,84,80;,
 4;179,175,83,87;,
 4;177,179,87,178;,
 4;180,181,159,158;,
 4;181,182,160,159;,
 4;181,180,183,182;,
 4;184,180,158,161;,
 4;185,184,161,162;,
 4;180,184,185,183;,
 4;182,186,163,160;,
 4;182,183,187,186;,
 4;188,185,162,164;,
 4;183,185,188,187;,
 4;189,190,166,165;,
 4;186,189,165,163;,
 4;186,187,190,189;,
 4;191,188,164,168;,
 4;190,191,168,166;,
 4;187,188,191,190;,
 4;192,193,170,169;,
 4;193,194,171,170;,
 4;193,192,195,194;,
 4;196,192,169,172;,
 4;197,196,172,173;,
 4;192,196,197,195;,
 4;194,198,174,171;,
 4;194,195,199,198;,
 4;200,197,173,175;,
 4;195,197,200,199;,
 4;201,202,177,176;,
 4;198,201,176,174;,
 4;198,199,202,201;,
 4;203,200,175,179;,
 4;202,203,179,177;,
 4;199,200,203,202;;
 
 MeshMaterialList {
  2;
  156;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
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
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  0,
  1;;
  Material {
   0.800000;0.000000;0.122353;1.000000;;
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
 }
 MeshNormals {
  48;
  -0.626156;0.511337;-0.588611;,
  -0.255464;0.534317;-0.805756;,
  0.000000;0.498999;-0.866603;,
  0.255464;0.534317;-0.805756;,
  -0.153371;0.153982;-0.976098;,
  -0.128467;0.128871;-0.983305;,
  0.000000;0.079617;-0.996826;,
  0.128467;0.128871;-0.983305;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.626156;0.511337;-0.588611;,
  0.804663;0.543750;-0.238439;,
  0.863758;0.503819;-0.009389;,
  0.799056;0.519537;0.302640;,
  0.153371;0.153982;-0.976098;,
  0.979118;0.161238;-0.123814;,
  0.993919;0.109578;-0.010808;,
  0.971227;0.159506;0.176851;,
  1.000000;0.000000;0.000000;,
  0.620019;0.477574;0.622495;,
  0.300686;0.521177;0.798725;,
  0.000000;0.502618;0.864508;,
  -0.300686;0.521177;0.798725;,
  0.840063;0.276578;0.466690;,
  0.176287;0.163090;0.970734;,
  0.000000;0.100894;0.994897;,
  -0.176287;0.163090;0.970734;,
  0.000000;0.000000;1.000000;,
  -0.620019;0.477574;0.622495;,
  -0.799056;0.519537;0.302640;,
  -0.863758;0.503819;-0.009389;,
  -0.804663;0.543750;-0.238439;,
  -0.465663;0.276487;0.840662;,
  -0.971227;0.159506;0.176851;,
  -0.993919;0.109578;-0.010808;,
  -0.979118;0.161238;-0.123814;,
  -1.000000;0.000000;0.000000;,
  -0.321117;0.890474;0.322396;,
  0.000000;0.952376;0.304925;,
  0.321117;0.890474;0.322396;,
  -0.307808;0.951443;-0.003344;,
  0.000000;1.000000;0.000000;,
  0.307808;0.951443;-0.003344;,
  -0.306718;0.905510;-0.293218;,
  0.000000;0.954390;-0.298562;,
  0.306718;0.905510;-0.293218;,
  0.975128;0.182444;-0.125857;,
  -0.975128;0.182444;-0.125857;;
  156;
  4;0,1,5,4;,
  4;1,2,6,5;,
  4;2,3,7,6;,
  4;3,10,14,7;,
  4;4,5,8,8;,
  4;7,14,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;10,11,15,46;,
  4;11,12,16,15;,
  4;12,13,17,16;,
  4;13,19,23,17;,
  4;46,15,18,18;,
  4;17,23,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;19,20,24,23;,
  4;20,21,25,24;,
  4;21,22,26,25;,
  4;22,28,32,26;,
  4;27,24,27,27;,
  4;26,32,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,29,33,32;,
  4;29,30,34,33;,
  4;30,31,35,34;,
  4;31,0,47,35;,
  4;36,33,36,36;,
  4;35,47,36,36;,
  4;36,36,36,36;,
  4;36,36,36,36;,
  4;36,36,36,36;,
  4;36,36,36,36;,
  4;28,22,37,29;,
  4;22,21,38,37;,
  4;21,20,39,38;,
  4;20,19,13,39;,
  4;29,37,40,30;,
  4;37,38,41,40;,
  4;38,39,42,41;,
  4;39,13,12,42;,
  4;30,40,43,31;,
  4;40,41,44,43;,
  4;41,42,45,44;,
  4;42,12,11,45;,
  4;31,43,1,0;,
  4;43,44,2,1;,
  4;44,45,3,2;,
  4;45,11,10,3;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;18,18,18,18;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;36,36,36,36;,
  4;8,8,8,8;,
  4;18,18,18,18;,
  4;8,8,8,8;,
  4;36,36,36,36;,
  4;8,8,8,8;,
  4;41,41,41,41;,
  4;18,18,18,18;,
  4;8,8,8,8;,
  4;36,36,36,36;,
  4;41,41,41,41;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;36,36,36,36;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;18,18,18,18;,
  4;27,27,27,27;,
  4;36,36,36,36;,
  4;27,27,27,27;,
  4;18,18,18,18;,
  4;27,27,27,27;,
  4;41,41,41,41;,
  4;36,36,36,36;,
  4;27,27,27,27;,
  4;18,18,18,18;,
  4;41,41,41,41;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;27,27,27,27;,
  4;8,8,8,8;,
  4;41,41,41,41;,
  4;27,27,27,27;,
  4;8,8,8,8;,
  4;41,41,41,41;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;8,8,8,8;,
  4;27,27,27,27;,
  4;41,41,41,41;,
  4;8,8,8,8;,
  4;27,27,27,27;,
  4;41,41,41,41;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;18,18,18,18;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;18,18,18,18;,
  4;27,27,27,27;,
  4;18,18,18,18;,
  4;8,8,8,8;,
  4;18,18,18,18;,
  4;41,41,41,41;,
  4;27,27,27,27;,
  4;18,18,18,18;,
  4;8,8,8,8;,
  4;41,41,41,41;,
  4;18,18,18,18;,
  4;9,9,9,9;,
  4;8,8,8,8;,
  4;36,36,36,36;,
  4;9,9,9,9;,
  4;27,27,27,27;,
  4;36,36,36,36;,
  4;8,8,8,8;,
  4;36,36,36,36;,
  4;27,27,27,27;,
  4;36,36,36,36;,
  4;41,41,41,41;,
  4;8,8,8,8;,
  4;36,36,36,36;,
  4;27,27,27,27;,
  4;41,41,41,41;,
  4;36,36,36,36;;
 }
 MeshTextureCoords {
  204;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  1.000000;0.750000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.250000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;;
 }
}
