"""Module providing a docloader."""
from langchain.document_loaders import HNLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
loader = HNLoader("https://news.ycombinator.com/item?id=34422627")
data = loader.load()
print(f"Found {len(data)} comments")
print(f"Here's a sample:\n\n{''.join([x.page_content[:150] for x in data[:2]])}")

#Download txt from https://paulgraham.com/worked.html
with open('./worked.txt', encoding="utf-8") as f:
    pg_work = f.read()
print(f"You have {len([pg_work])} document")

text_splitter = RecursiveCharacterTextSplitter(
    chunk_size = 150,
    chunk_overlap = 20,
)

texts = text_splitter.create_documents([pg_work])
print(f"You have {len(texts)} documents")
print("Preview:")
print(texts[0].page_content, "\n")
print(texts[1].page_content)
