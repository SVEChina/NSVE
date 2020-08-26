{
    "shadertype" : "metal",
    "name" : "back",
    "file": "shader/back.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "direct",
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
