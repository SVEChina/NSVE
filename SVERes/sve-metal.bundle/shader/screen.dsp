{
    "shadertype" : "metal",
    "name" : "screen",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "vs": {
        "entry": "vertexShader"
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {   "chn" : 0 ,
                "warp-s" : "SV_V_WRAP_CLAMP" ,
                "warp-t" : "SV_V_WRAP_CLAMP" ,
                "min" : "SV_V_FILTER_LINEAR",
                "mag" : "SV_V_FILTER_LINEAR" }
        ]
    }
}
