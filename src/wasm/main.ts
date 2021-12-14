console.log("wasm test init...");

import { MatComputerDemo } from "./app/MatComputerDemo";
import { TransformDemo } from "./app/TransformDemo";

// let demoIns = new MatComputerDemo();
let demoIns = new TransformDemo();

class WasmCore {
    static Module: any = null;
}
/*
class AppDemo
{
    constructor()
    {
    }
    initialize():void
    {
        //getTestBytes,showVersion
        let module:any = WasmCore.Module;
        module.showVersion();
        let u8arr:any = module.getTestBytes();
        console.log("A u8arr, ",u8arr);
        u8arr[0] = 13;
        u8arr = module.getTestBytes();
        console.log("B u8arr, ",u8arr);
        let value:number = module.getSumBytes();
        console.log("value, ",value);
        function funvscall(vs:any)
        {
            console.log("funvscall,vs: ",vs);
        }
        module.callWithMemoryView(funvscall);
        let pvs:Uint16Array = new Uint16Array([32,12,56,887]);
        value = module.emval_test_sum(pvs);
        //
        console.log("emval_test_sum,value: "+value);
        module.testMathDemo();
        let ClassModule:any = module;
        let pclass = ClassModule.DemoMain;
        if(pclass != null)
        {
            let demoMain = new pclass();
            demoMain.initialize();
            demoMain.delete();
            //
            //ConstClassType
            console.log("ClassModule.TestClass.ConstClassType",ClassModule.TestClass.ConstClassType);
            console.log("A ClassModule.TestClass.ClassType",ClassModule.TestClass.ClassType);
            ClassModule.TestClass.ClassType = 109;
            console.log("B ClassModule.TestClass.ClassType",ClassModule.TestClass.ClassType);
            let testClassIns:any = new ClassModule.TestClass(12,"TestClass ins");
            //type
            console.log("testClassIns.type",testClassIns.type);
            testClassIns.initialize();
            //testClassIns.delete();
        }
        else
        {
            console.log("Error: pclass is null.");
        }
    }
    run():void
    {
    }
}
//0049f86d2f30ce3d108686631728b2b868e3f97a
let demoIns:AppDemo = new AppDemo();
*/
function main(): void {
    console.log("---- demo --- init --");
    demoIns.initialize(WasmCore.Module);
    function mainLoop(now: any): void {
        demoIns.run();
        window.requestAnimationFrame(mainLoop);
    }
    window.requestAnimationFrame(mainLoop);
    console.log("---- demo --- running --");
}

class WasmLoader {
    wasmModule: any = null;
    constructor() {
    }
    private moduleLoaded(pmodule: any): void {
        console.log("WasmLoader::moduleLoaded(), wasm compile ok, pmodule: ", pmodule);
        this.wasmModule = pmodule;
        WasmCore.Module = this.wasmModule;
        main();
    }
    initWasm(): void {
        let pwindow: any = window;
        //let path:string = "wasm/demomain.js";
        //let path:string = "wasm/matDemo.js";
        //let path:string = "wasm/voxcgw.js";
        let path: string = "wasm/transformDemo.js";
        let decoder_script: any = document.getElementById("wasm_script");
        if (decoder_script !== null) {
            return;
        }
        let head: any = document.getElementsByTagName("head")[0];
        let element: any = document.createElement("script");
        element.id = "decoder_script";
        element.type = "text/javascript";
        element.src = path;
        let times: number = 0;
        let selfT: any = this;
        element.onload = function (dracoDecoder: any) {
            console.log("loaded wasm wapper js.");
            if (pwindow["Module"] != undefined) {
                let module: any = pwindow["Module"];
                module["onRuntimeInitialized"] = function () {
                    console.log("onRuntimeInitialized do..");
                }
                module["onModuleLoaded"] = function (pmodule: any) {
                    selfT.moduleLoaded(pmodule);
                    console.log("onModuleLoaded run end..");
                };

            }
        }
        head.appendChild(element);
    }
}

let wloader: WasmLoader = new WasmLoader();
wloader.initWasm();
