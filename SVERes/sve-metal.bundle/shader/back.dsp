{
    "shadertype" : "metal",
    "name" : "back",
    "file": "shader/back.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "reback",
    "vs": {
        "entry": "vertexShader"
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {   "chn" : 0 }
        ]
    }
}
