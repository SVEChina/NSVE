{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/filter/filterLUT.fs",
    "sampler": [
        { "name" : "aTexture0", "stage" : 1 , "chn" : 0 },
        { "name" : "aLut", "stage" : 1 , "chn" : 1 } ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "u_invert", "type" : "fvec2", "value" : "1.0,1.0" },
                { "name" : "tex0size", "type" : "fvec2", "value" : "1.0,1.0" } ]
        }
    ]
}

