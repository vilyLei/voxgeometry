const path = require('path');
const resolve = dir => path.join(__dirname, dir);
const { ENV = '' } = process.env;

module.exports = {
  pages: {
    index: {
      entry: process.env.NODE_ENV === 'production' ? './src/wasm/main.ts' : './src/wasm/main.ts'
    }
  },
  filenameHashing: false,
  // 是否为生产环境构建生成 source map
  productionSourceMap: false,

  configureWebpack: config => {
    // TODO: ~entry in ./node_modules/@vue/cli-service/lib/commands/build/entry-lib.js
    // config['resolve'] = {
    //   extensions: ['.tsx', '.ts', '.js', '.glsl'],
    //   alias: {}
    // };
    if (['pro'].includes(ENV)) {
      config.optimization.minimizer[0].options.terserOptions.compress.warnings = false;
      config.optimization.minimizer[0].options.terserOptions.compress.drop_console = true;
      config.optimization.minimizer[0].options.terserOptions.compress.drop_debugger = true;
      config.optimization.minimizer[0].options.terserOptions.compress.pure_funcs = [
        'console.log'
      ];
    }
  },

  devServer: {
    port: 9000,
    disableHostCheck:true
    // https:true
  },

  chainWebpack: config => {
    config.module
      .rule('glsl')
      .test(/\.glsl$/)
      .use('raw')
      .loader('raw-loader')
      .end();
  }
};
