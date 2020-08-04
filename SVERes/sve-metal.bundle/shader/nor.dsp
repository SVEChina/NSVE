{
    "shadertype" : "metal",
    "name" : "nor",
    "file": "shader/screen.metal",
    "vs": {
        "entry": "vertexShader",
        "formate" : "E_VF_V2_T0",
        "sampler": [
            { "chn" : 0 , "warp-s" : "default" ,  "warp-t" : "default" , "min" : "default", "mag" : "default" }
        ],
        "uniform": [
            { "name" : "test-fmat4", "type" : "fmat4", "value" : "identity" }
        ]
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            { "chn" : 0 , "warp-s" : "default" ,  "warp-t" : "default" , "min" : "default", "mag" : "default" }
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
