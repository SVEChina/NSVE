{
    "shadertype" : "metal",
    "name" : "filter-lut",
    "file": "shader/filter-lut.metal",
    "formate" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs": {
        "entry": "vsMain"
    },
    "fs":{
        "entry": "fsMain",
        "sampler": [
            { "chn" : 0 }
        ]
    }
}
