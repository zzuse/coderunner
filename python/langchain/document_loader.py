from langchain.document_loaders import HNLoader
loader = HNLoader("https://news.ycombinator.com/item?id=34422627")
data = loader.load()
print(f"Found {len(data)} comments")
print(f"Here's a sample:\n\n{''.join([x.page_content[:150] for x in data[:2]])}")