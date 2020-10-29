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
                        { "name" : "matModel", "type" : "fmat4", "value" : "null" },
                        { "name" : "matV", "type" : "fmat4", "value" : "null" },
                        { "name" : "matP", "type" : "fmat4", "value" : "null" }
                    ]
        }
    ]
}
