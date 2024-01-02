import easyocr


def is_text_present(image_path):
    reader = easyocr.Reader(['en'])
    result = reader.readtext(image_path)
    if len(result) > 0:
        for (bbox, text, prob) in result:
            print(text)


print(is_text_present('/Users/zhangzhen/Downloads/unnamed.jpg'))
