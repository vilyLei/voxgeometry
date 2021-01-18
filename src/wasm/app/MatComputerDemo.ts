
//export MatComputerDemo
export namespace app
{
    export class MatComputerDemo
    {
        constructor()
        {
        }
        initialize(module:any):void
        {
            console.log("MatComputerDemo::initialize() A.....");
            module.showVersion();
        }
        initialize3(module:any):void
        {
            console.log("MatComputerDemo::initialize() A.....");
            module.showVersion();
            let ClassModule:any = module;
            let pclass = ClassModule.MatrixComputer;
            if(pclass != null)
            {
                console.log(">>>>>>>>>>> MatrixComputer calc >>>>>>>>>>>");
                let index:number = 0;
                let matCompter:any = new pclass();
                matCompter.allocate(16);
                //  matCompter.setScaleXYZParamAt(10.0, 4.5, 2.1, index);
                //  matCompter.setRotationEulerAngleParamAt(30.0, 20.0, 80.0, index);
                //  matCompter.setTranslationXYZParamAt(30.0, 20.0, 80.0, index);
                let paramFS32:any = matCompter.getParamData();
                console.log("A paramFS32: ",paramFS32);
                let subParamFS32:Float32Array = new Float32Array([10.0, 4.5, 2.1, 30.0, 20.0, 80.0, 30.0, 20.0, 80.0]);
                paramFS32.set(subParamFS32, 0);
                console.log("B paramFS32: ",paramFS32);
                matCompter.calc(1);
                //matCompter.identityAt(0);
                matCompter.coutThisMatAt(0);
                let u8arr:any = matCompter.getMatData();
                console.log("matCompter.getMatData(), u8arr.length: "+u8arr.length);
                console.log("matCompter.getMatData(), u8arr: ", u8arr);
                console.log("matCompter.getIData(): ", matCompter.getIData());

                //  let u8arr:any = module.getTestBytes();
                //  console.log("u8arr.length: ",u8arr.length);
            }
            else
            {
                console.log("Error: pclass is null.");
            }
            //          //
            //          let pdIns:any = new ClassModule.CarDemo("pdIns,CarDemo",5);
            //          if(pdIns != null)
            //          {
            //              console.log(">>>>>>>>>>> ClassModule.CarDemo >>>>>>>>>>>");
            //              let dataArr:any = pdIns.getTestBytes();
            //              console.log("pdIns dataArr.length: ",dataArr.length);
            //              console.log("dataArr: ",dataArr);
            //          }
            //          else
            //          {
            //          }
        }
        initialize2(module:any):void
        {
            console.log("MatComputerDemo::initialize().....");
            //getTestBytes,showVersion
            //let module:any = WasmCore.Module;
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
            console.log("-------------------------------------------");
        }
        run():void
        {
        }
    }
}