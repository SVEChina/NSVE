{
    "shadertype" : "metal",
    "name" : "nor",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "nor",
    "vs": {
        "entry": "vsMain"
    },
    "fs":{
        "entry": "fsMain",
        "sampler": [ { "chn" : 0 } ]
    }
}
