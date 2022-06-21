const OPENING = "(";
const CLOSING = ")";

const calculateBracketCount = (str) => {
    const length = str.length;

    let opening = 0;
    let closing = 0;

    for(let i = 0; i < length; ++i) {
        const char = str[i];

        if(char === OPENING) ++opening;
        else if(char === CLOSING) ++closing;
    }

    return opening < closing ? opening: closing;
};

module.export = calculateBracketCount;
