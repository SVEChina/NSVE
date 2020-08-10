{
    "shadertype" : "metal",
    "name" : "sprite",
    "file": "shader/sprite.metal",
    "formate" : ["E_V3","E_T0"],
    "vs": {
        "entry": "vertexShader",
        "uniform": [
            {
                "bufID" : 1,
                "tbl" : [
                            { "name" : "matw", "type" : "fmat4", "value" : "null" },
                            { "name" : "matvp", "type" : "fmat4", "value" : "null" }
                        ]
            }
        ]
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
