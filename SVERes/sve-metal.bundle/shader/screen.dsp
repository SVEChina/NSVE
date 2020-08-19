{
    "shadertype" : "metal",
    "name" : "screen",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "post",
    "vs": {
        "entry": "vertexShader"
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {   "chn" : 0  }
        ]
    }
}
