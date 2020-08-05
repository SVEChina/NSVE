{
    "shadertype" : "metal",
    "name" : "sprite",
    "file": "shader/sprite.metal",
    "formate" : "E_VF_V3_T0",
    "vs": {
        "entry": "vertexShader"
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {   "chn" : 0 ,
                "warp-s" : "SV_V_WRAP_BORDER" ,
                "warp-t" : "SV_V_WRAP_BORDER" ,
                "min" : "SV_V_FILTER_LINEAR",
                "mag" : "SV_V_FILTER_LINEAR" }
        ]
    }
}
