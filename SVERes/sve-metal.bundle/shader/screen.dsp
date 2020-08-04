{
    "shadertype" : "metal",
    "name" : "screen",
    "file": "shader/screen.metal",
    "vs": {
        "entry": "vertexShader",
        "formate" : "E_VF_V2_T0",
        "sampler": [
            { "chn" : 0 , "warp-s" : "default" ,  "warp-t" : "default" , "min" : "default", "mag" : "default" }
        ],
        "uniform": [
            { "name" : "test-f32", "type" : "f32", "value" : "1.23456" }
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
