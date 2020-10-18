{
    "file": "shader/code/sprite.metal",
    "vdsp" : ["E_V3","E_T0"],
    "pass" : "nor",
    "vs" : 1,
    "fs" : 1,
    "sampler": [ { "stage" : 1, "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 0,
            "bufID" : 1,
            "tbl" : [
                        { "name" : "matw", "type" : "fmat4", "value" : "null" },
                        { "name" : "matv", "type" : "fmat4", "value" : "null" },
                        { "name" : "matp", "type" : "fmat4", "value" : "null" }
                    ]
        }
    ]
}
