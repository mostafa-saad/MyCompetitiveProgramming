commentSettings = {
    nameSpace: 'miu-comment',
    previewParserPath:  '',
    onShiftEnter:       {keepDefault:false, openWith:'\n\n'},
    markupSet: [
        {name:'Bold', key:'B', openWith:'**', closeWith:'**'},
        {name:'Italic', key:'I', openWith:'_', closeWith:'_'},
        {separator:'---------------' },
        {name:'Bulleted List', openWith:'- ' },
        {name:'Numeric List', openWith:function(markItUp) {
            return markItUp.line+'. ';
        }},
        {separator:'---------------' },
//        {name:'Picture', key:'P', replaceWith:'![[![Alternative text]!]]([![Url:!:http://]!] "[![Title]!]")'},
        {name:'Picture', key:'P', replaceWith:'![ ]([![Url:!:http://]!])'},
//        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!] "[![Title]!]")', placeHolder:'Your text to link here...' },
        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!])', placeHolder:'Your text to link here...' },
        {separator:'---------------'},
        {name:'Source Code', dropMenu: [
            {name:'Block', multiline:true, openBlockWith:function(h) {
                if (h.selection.substr(0) == '\n')
                    return "\n~~~~~";
                else
                    return "\n~~~~~\n";
            }, closeBlockWith:function(h) {
                if (h.selection.substr(-1) == '\n')
                    return "~~~~~\n\n";
                else
                    return "\n~~~~~\n\n";
            }, placeHolder:'Your code here...' },
            {name:'Inline', openWith:'\`', closeWith:'\`'}
        ]},
        {separator:'---------------'},
        {name:'Codeforces Tags', dropMenu: [
            { name:'User',     replaceWith:'[user:[![User handle]!]]'},
            { name:'Submission',     replaceWith:'[submission:[![Submission ID (example: 1010182)]!]]'},
            { name:'Problem',     replaceWith:'[problem:[![Problem Code (example: 12A)]!]]'},
            { name:'Contest',   replaceWith:'[contest:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Standings', replaceWith:'[standings:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Spoiler', replaceWith:'<spoiler summary="[![Summary:!:Spoiler]!]">\n...\n</spoiler>'}
          ] }

    ]
}

completeSettings = {
    nameSpace: 'miu-complete',
    previewParserPath:  '',
    onShiftEnter:       {keepDefault:false, openWith:'\n\n'},
    markupSet: [
        {name:'First Level Heading', key:'1', placeHolder:'Your title here...', closeWith:function(markItUp) { return miu.markdownTitle(markItUp, '=') } },
        {name:'Second Level Heading', key:'2', placeHolder:'Your title here...', closeWith:function(markItUp) { return miu.markdownTitle(markItUp, '-') } },
        {name:'Heading 3', key:'3', openWith:'### ', placeHolder:'Your title here...' },
        {name:'Heading 4', key:'4', openWith:'#### ', placeHolder:'Your title here...' },
        {separator:'---------------' },     
        {name:'Bold', key:'B', openWith:'**', closeWith:'**'},
        {name:'Italic', key:'I', openWith:'_', closeWith:'_'},
        {separator:'---------------' },
        {name:'Bulleted List', openWith:'- ' },
        {name:'Numeric List', openWith:function(markItUp) {
            return markItUp.line+'. ';
        }},
        {separator:'---------------' },
//        {name:'Picture', key:'P', replaceWith:'![[![Alternative text]!]]([![Url:!:http://]!] "[![Title]!]")'},
        {name:'Picture', key:'P', replaceWith:'![ ]([![Url:!:http://]!])'},
//        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!] "[![Title]!]")', placeHolder:'Your text to link here...' },
        {name:'Link', key:'L', openWith:'[', closeWith:']([![Url:!:http://]!])', placeHolder:'Your text to link here...' },
        {separator:'---------------'},  
        {name:'Source Code', dropMenu: [
            {name:'Block', multiline:true, openBlockWith:function(h) {
                if (h.selection.substr(0) == '\n')
                    return "\n~~~~~";
                else
                    return "\n~~~~~\n";
            }, closeBlockWith:function(h) {
                if (h.selection.substr(-1) == '\n')
                    return "~~~~~\n\n";
                else
                    return "\n~~~~~\n\n";
            }, placeHolder:'Your code here...' },
            {name:'Inline', openWith:'\`', closeWith:'\`'}
        ]},
        {separator:'---------------'},
        {name:'Codeforces Tags', dropMenu: [
            { name:'User', replaceWith:'[user:[![User handle]!]]'},
            { name:'Submission', replaceWith:'[submission:[![Submission ID (example: 1010182)]!]]'},
            { name:'Problem', replaceWith:'[problem:[![Problem Code (example: 12A)]!]]'},
            { name:'Contest', replaceWith:'[contest:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Contest time', replaceWith:'[contest_time:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Standings', replaceWith:'[standings:[![Contest ID (from URL, example: 123)]!]]'},
            { name:'Spoiler', replaceWith:'<spoiler summary="[![Summary:!:Spoiler]!]">\n...\n</spoiler>'}
          ] }

    ]
}

// mIu nameSpace to avoid conflict.
miu = {
    markdownTitle: function(markItUp, char) {
        heading = '';
        n = $.trim(markItUp.selection||markItUp.placeHolder).length;
        for(i = 0; i < n; i++) {
            heading += char;
        }
        return '\n'+heading;
    }
}

