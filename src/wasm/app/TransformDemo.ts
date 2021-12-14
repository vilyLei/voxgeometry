class TransformDemo {
    constructor() {
    }
    initialize(classModule: any): void {
        //this.testAStar(classModule);
        this.testTrans(classModule);
    }

    private testTrans(classModule: any): void {
        let transIns: any = new classModule.MatTransform();
        console.log("transIns: ",transIns);
    }

    private testAStar(classModule: any): void {

        let descriptor: any = { rn: 6, cn: 6, stvs: null };
        descriptor.stvs = new Uint16Array(
            [
                0, 0, 0, 0, 0, 0,
                0, 0, 1, 1, 0, 0,
                0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 0,
                0, 0, 0, 1, 0, 0,
                0, 0, 0, 0, 0, 0
            ]
        );
        this.initializeAStar(classModule, descriptor);
    }

    private initializeAStar(classModule: any, descriptor: any): void {

        let aStar: any = new classModule.StarA();
        console.log("aStar: ", aStar);
        let rn = descriptor.rn;//6;
        let cn = descriptor.cn;//6;
        let stvs = descriptor.stvs;//6;
        aStar.allocate(rn * cn + 32);
        aStar.initialize(rn, cn, 100);
        let r = 0;
        let c = 0;
        let tot = rn * cn;
        let i = 0;
        for (; i < tot; ++i) {
            aStar.setGoValueByRC(stvs[i], r, c);
            c++;
            if (c >= cn) {
                c = 0;
                r++;
            }
        }

        let dataLen = 0;
        let vs = null;
        descriptor = { r0: 1, c0: 1, r1: 4, c1: 3 };
        console.log("0 ############## path descriptor: ", descriptor);
        aStar.searchPathDataByRC(descriptor.r0, descriptor.c0, descriptor.r1, descriptor.c1);
        dataLen = aStar.getPathDataTotal();
        vs = aStar.getPathData();
        console.log("serach 0 path dataLen: " + dataLen);
        console.log("serach 0 path vs: ", vs);

        descriptor = { r0: 1, c0: 1, r1: 4, c1: 3 };
        console.log("1 ############## path descriptor: ", descriptor);
        aStar.searchPathDataByRC(descriptor.r0, descriptor.c0, descriptor.r1, descriptor.c1);
        dataLen = aStar.getPathDataTotal();
        vs = aStar.getPathData();
        console.log("serach 1 path dataLen: " + dataLen);
        console.log("serach 1 path vs: ", vs);
    }
    run(): void {
    }
}
export { TransformDemo }