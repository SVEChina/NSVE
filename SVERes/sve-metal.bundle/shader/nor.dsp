{
    "shadertype" : "metal",
    "name" : "nor",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "nor",
    "vs": {
        "entry": "vertexShader"
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            { "chn" : 0 }
        ]
    }
}
