{
    "vdsp" : ["E_V3","E_T0"],
    "pass" : "nor",
    "vs" : "shader/code/normal3d.vs",
    "fs" : "shader/code/normal.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 0,
            "bufID" : 1,
            "tbl" : [
                        { "name" : "matw", "type" : "fmat4", "value" : "null" },
                        { "name" : "matvp", "type" : "fmat4", "value" : "null" }
                    ]
        }
    ]
}
