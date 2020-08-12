{
    "shadertype" : "metal",
    "name" : "nor",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "vs": {
        "entry": "vertexShader"
    },
    "fs":{
        "entry": "fragmentShader",
        "sampler": [
            {
                "chn" : 0 ,
                "warp-s" : "default" ,
                "warp-t" : "default" ,
                "min" : "default",
                "mag" : "default"
            }
        ]
    }
}
