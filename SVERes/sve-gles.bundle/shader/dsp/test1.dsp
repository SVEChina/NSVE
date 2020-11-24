{
    "vdsp" : ["E_V3","E_T0","E_BONE","E_BONEW"],
    "pass" : "nor",
    "vs" : "shader/code/test1.vs",
    "fs" : "shader/code/test1.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 0,
            "bufID" : 1,
            "tbl" : [
                        { "name" : "matModel", "type" : "fmat4", "value" : "null" },
                        { "name" : "matVP", "type" : "fmat4", "value" : "null" },
                        { "name" : "texcoordClip", "type" : "fvec2", "value" : "null" }
                    ]
        }
    ]
}

