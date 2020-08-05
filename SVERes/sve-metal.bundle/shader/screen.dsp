{
    "shadertype" : "metal",
    "name" : "screen",
    "file": "shader/screen.metal",
    "formate" : "E_VF_V2_T0",
    "vs": {
        "entry": "vertexShader",
        "sampler": [
            {   "chn" : 0 ,
                "warp-s" : "SV_V_WRAP_CLAMP" ,
                "warp-t" : "SV_V_WRAP_CLAMP" ,
                "min" : "SV_V_FILTER_LINEAR",
                "mag" : "SV_V_FILTER_LINEAR"    }
        ],
        "uniform": [
            { "name" : "test-f32", "type" : "f32", "value" : "1.23456" }
        ]
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {   "chn" : 0 ,
                "warp-s" : "SV_V_WRAP_CLAMP" ,
                "warp-t" : "SV_V_WRAP_CLAMP" ,
                "min" : "SV_V_FILTER_LINEAR",
                "mag" : "SV_V_FILTER_LINEAR"    }
        ]
    },
    "gs": {
        "entry": "null"
    },
    "tse": {
        "entry": "null"
    },
    "tsd": {
        "entry": "null"
    }
}
