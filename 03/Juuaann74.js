function isColor(color) {
    return /^#[0-9A-F]{6}$/i.test(color);
}

console.log(isColor('#bada55'));
