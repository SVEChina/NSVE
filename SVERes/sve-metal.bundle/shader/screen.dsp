{
    "shadertype" : "metal",
    "name" : "screen",
    "file": "shader/screen.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs": {
        "entry": "vsMain"
    },
    "fs":{
        "entry": "fsMain",
        "sampler": [ { "chn" : 0 } ]
    }
}
