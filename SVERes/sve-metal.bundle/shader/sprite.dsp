{
    "shadertype" : "metal",
    "name" : "sprite",
    "file": "shader/sprite.metal",
    "formate" : ["E_V3","E_T0"],
    "pass" : "nor",
    "vs": {
        "entry": "vertexShader",
        "uniform": [
            {
                "bufID" : 1,
                "tbl" : [
                            { "name" : "matw", "type" : "fmat4", "value" : "null" },
                            { "name" : "matv", "type" : "fmat4", "value" : "null" },
                            { "name" : "matp", "type" : "fmat4", "value" : "null" }
                        ]
            }
        ]
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {   "chn" : 0 }
        ]
    }
}
