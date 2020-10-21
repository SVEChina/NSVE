{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/filter/filterHDR.fs",
    "sampler": [
        { "name" : "hdr_img", "stage" : 1 , "chn" : 0 }],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "hdr_size", "type" : "fvec2", "value" : "1.0,1.0" }
            ]
        }
    ]
}
