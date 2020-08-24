{
    "shadertype" : "metal",
    "name" : "screenCamera",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "target-c",
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
