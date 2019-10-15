'use strict'

module.exports = (ctx) => ({
  map: ctx.file.dirname.includes('examples') ? false : {
    inline: false,
    annotation: true,
    sourcesContent: true
  },
  plugins: {
    'autoprefixer': {
      cascade: false,
      overrideBrowserslist: ['last 2 versions', '> 1%', 'ie >= 10']
    },
    'postcss-assets': {
      cachebuster: true,
      relative: true,
      loadPaths: ['images']
    }
  }
})
